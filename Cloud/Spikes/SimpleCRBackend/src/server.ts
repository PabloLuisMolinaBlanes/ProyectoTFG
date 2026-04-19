/*Imports*/
import express from 'express'
import cors from 'cors'
import { PrismaClient } from "./generated/prisma";
import { PrismaMariaDb } from "@prisma/adapter-mariadb";

/*Database setup*/
const adapter = new PrismaMariaDb({
  host: process.env.DATABASE_HOST,
  user: process.env.DATABASE_USER,
  password: process.env.DATABASE_PASSWORD,
  database: process.env.DATABASE_NAME,
  connectionLimit: 5,
});
const prisma : PrismaClient = new PrismaClient({ adapter });

/*ORM functions*/
async function createTest(id_received: string, hospital_password: string, first_exam: string, second_exam_first_potentio: string, second_exam_second_potentio: string) {
    const hospital_received = await prisma.profile.findFirst({
        where: {
            password: hospital_password
        } 
    })
    if (hospital_received == undefined) {
        return {error: "Invalid password"};
    } 
    const test = await prisma.test.create({
        data: {
            id: id_received,
            results_reaction_time: first_exam,
            results_first_potentiometer: second_exam_first_potentio,
            results_second_potentiometer: second_exam_second_potentio,
            hospital_id: hospital_received.hospital_id
        }
    })
    return test;
}

async function getAllTestsPerHospital(hospital_password: string) {
    const hospital_received = await prisma.profile.findFirst({
        where: {
            password: hospital_password
        } 
    })
    if (hospital_received == undefined) {
        return {error: "Invalid password"};
    } 
    const tests = await prisma.test.findMany({
        where: {
            hospital_id: hospital_received.hospital_id
        } 
    });
    return tests;
}

/*Server*/
const app = express()
const corsOptions = {
    origin: 'localhost:5000',
    optionsSuccessStatus: 200
}
const port = 3000

app.use(cors(corsOptions))
app.use(express.json())
app.use(express.urlencoded({extended: true}))

app.post("/upload", async (req,res) => {
    return (JSON.stringify(await createTest(req.body.id, req.body.hospital_password, req.body.first_exam, req.body.second_exam_first_potentio, req.body.second_exam_second_potentio)));
});

app.get("/receive", async (req,res) => {
    return (JSON.stringify(await getAllTestsPerHospital(req.body.hospital_password)));
});

app.listen(port, () => {
    console.log(`Cloud backend server is now listening in port ${port}`)
})