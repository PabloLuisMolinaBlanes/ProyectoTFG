/*Imports*/
import express, {Request}  from 'express'
import cors from 'cors'
import {createTest, getAllTestsPerHospital} from './crud'
const { loadEnvFile } = require('node:process');
loadEnvFile(__dirname + '/../../.env');

/*Types*/
interface RequestData {
    hospital_password: string,
    hospital_name: string
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