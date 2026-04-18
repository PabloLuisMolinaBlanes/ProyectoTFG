/*Imports*/
import express from 'express'
import cors from 'cors'
import { PrismaClient, Profile, Test} from "./generated/prisma";
const prisma : PrismaClient = new PrismaClient()
import { AxiosResponse } from 'axios'

/*ORM functions*/

/*Server*/
const app = express()
const corsOptions = {
    origin: 'http://localhost:5173',
    optionsSuccessStatus: 200
}
const axios = require("axios")
const port = 3000

app.use(cors(corsOptions))
app.use(express.json())
app.use(express.urlencoded({extended: true}))

app.post("/upload", async (req,res) => {
    console.log("Received: " + JSON.stringify(req.body))
});

app.get("/receive", async (req,res) => {
    console.log("Received: " + JSON.stringify(req.body))
});

app.listen(port, () => {
    console.log(`Cloud backend server is now listening in port ${port}`)
})