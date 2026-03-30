import express from 'express'
import cors from 'cors'
import { AxiosResponse } from 'axios'

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
    /*axios.post("http://localhost:5000/", req.body).then((response : AxiosResponse) => {
        res.setHeader('content-type', 'text/plain')
        res.send(response.data)
    })*/
});

app.listen(port, () => {
    console.log(`ResultServer Test backend server is now listening in port ${port}`)
})