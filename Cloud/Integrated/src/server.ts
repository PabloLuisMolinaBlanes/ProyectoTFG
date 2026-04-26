/*Imports*/
import express, {Request}  from 'express'
import cors from 'cors'
import bcrypt from 'bcrypt'
const { loadEnvFile } = require('node:process');
loadEnvFile(__dirname + '/../../.env');
import { PrismaClient } from "./generated/prisma";
import { PrismaMariaDb } from "@prisma/adapter-mariadb";

/*Types*/
interface RequestData {
    hospital_password: string,
    hospital_name: string
}

/*ORM connection to database setup*/
const adapter = new PrismaMariaDb({
  host: process.env.DATABASE_HOST,
  port: 3306,
  user: process.env.DATABASE_USER,
  password: process.env.DATABASE_PASSWORD,
  database: process.env.DATABASE_NAME,
  ssl: false,
  allowPublicKeyRetrieval: true,
  connectionLimit: 5,
});
const prisma : PrismaClient = new PrismaClient({ adapter });

/* Utils */

/*Genera un hash bcrypt2 de la clave enviada; con 10 iteraciones de semilla*/
async function hashPassword(password : string) : Promise<string> {
    return await bcrypt.hash(password, 10)
}

async function comparePasswords(password : string, passwordHash : string) : Promise<boolean> {
    return bcrypt.compare(password, passwordHash)
}

/*ORM functions*/

/*Devuelve un perfil de usuario según un nombre de hospital*/
async function getProfile(hospital_name: string) {
    const hospital_received = await prisma.profile.findFirst({
        where: {
            hospital: hospital_name
        } 
    })
    return hospital_received;
} 

/*Crea una examinación según datos recibidos*/
async function createTest(id_received: string, hospital_password: string, hospital_name: string, first_exam: string, second_exam_first_potentio: string, second_exam_second_potentio: string) {
    const hospital = await getProfile(hospital_name);
    if (hospital == undefined) {
        return {error: "No hospital found with that name"};;
    } 
    const passwordComparison = await comparePasswords(hospital_password, hospital.password);
    if (!passwordComparison) {
        return {error: "Wrong password"};
    } 
    const test = await prisma.test.create({
        data: {
            id: id_received,
            results_reaction_time: first_exam,
            results_first_potentiometer: second_exam_first_potentio,
            results_second_potentiometer: second_exam_second_potentio,
            hospital_id: hospital.hospital_id
        }
    })
    return test;
}

/*Obtiene todas las examinaciones de un hospital según datos recibidos*/
async function getAllTestsPerHospital(hospital_name: string, hospital_password: string) {
    const hospital_received = await getProfile(hospital_name);
    if (hospital_received == undefined) {
        return {error: "No hospital found with that name"};;
    }
    const passwordComparison = await comparePasswords(hospital_password, hospital_received.password);
    if (!passwordComparison) {
        return {error: "Wrong password"};
    }
    const tests = await prisma.test.findMany({
        where: {
            hospital_id: hospital_received.hospital_id
        } 
    });
    return tests;
}

/*Iniciacización de servidor y parámetros*/
const app = express()
const corsOptions = {
    origin: 'localhost:5000',
    optionsSuccessStatus: 200
}
const port = 3000

app.use(cors(corsOptions))
app.use(express.json())
app.use(express.urlencoded({extended: true}))

/*Métodos del servidor*/

/*Almacena datos de examinación de cliente local según datos en req*/
app.post("/upload", async (req,res) => {
    const result = await createTest(req.body.id, req.body.hospital_password, req.body.hospital_name, req.body.first_exam, req.body.second_exam_first_potentio, req.body.second_exam_second_potentio);
    const tosend = await JSON.stringify(result)
    res.send(tosend);
}); 

/*Manda datos de examinaciones a clientes locales según datos en req*/
app.get("/receive", async (req: Request<{},{},{},RequestData>,res) => {
    const result = await getAllTestsPerHospital(req.query.hospital_name, req.query.hospital_password)
    const tosend = await JSON.stringify(result)
    res.send(tosend);
});

/*Comienza a escuchar en puerto indicado*/
app.listen(port, () => {
    console.log(`Cloud backend server is now listening in port ${port}`)
})