/*Imports and definitions*/

import axios, { AxiosResponse } from 'axios'
import * as fs from 'fs';
import * as readline from "readline"

type nullable<T> = T | null | undefined

var tabla_de_residuos : String[]

var tabla_de_extranjeria : Map<String, number> = new Map();

const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
});

/*Types*/

type PostData = {
    id_received: string,
    hospital_password: string,
    hospital_name: string,
    first_exam: string,
    second_exam_first_potentio: string,
    second_exam_second_potentio: string
}

type Test = {
    id: string,
    results_reaction_time: string,
    results_first_potentiometer: string,
    results_second_potentiometer: string,
    hospital_id: number
}

/*Auxiliary functions*/

function initializeNIFArray() {
    tabla_de_residuos.push("T")
    tabla_de_residuos.push("R")
    tabla_de_residuos.push("W")
    tabla_de_residuos.push("A")
    tabla_de_residuos.push("G")
    tabla_de_residuos.push("M")
    tabla_de_residuos.push("Y")
    tabla_de_residuos.push("F")
    tabla_de_residuos.push("P")
    tabla_de_residuos.push("D")
    tabla_de_residuos.push("X")
    tabla_de_residuos.push("B")
    tabla_de_residuos.push("N")
    tabla_de_residuos.push("J")
    tabla_de_residuos.push("Z")
    tabla_de_residuos.push("S")
    tabla_de_residuos.push("Q")
    tabla_de_residuos.push("V")
    tabla_de_residuos.push("H")
    tabla_de_residuos.push("L")
    tabla_de_residuos.push("C")
    tabla_de_residuos.push("K")
    tabla_de_residuos.push("E")
    tabla_de_extranjeria.set("X",0)
    tabla_de_extranjeria.set("Y",1)
    tabla_de_extranjeria.set("Z",2) 
} 

async function sendData(data : PostData) : Promise<nullable<Test>>   {
    const dataPromise : Promise<AxiosResponse<nullable<Test>>> = axios.post("http://localhost:5000/upload", data).then((response : AxiosResponse) => {
        if (response.data != undefined) {
            return response.data;
        }
        return undefined;
    });
    return (await dataPromise).data
}

async function returnAllExaminations(hospital_name_received: string, hospital_password_received: string) : Promise<nullable<Test[]>> {
    const dataPromise : Promise<AxiosResponse<nullable<Test[]>>> = axios.post("http://localhost:5000/receive",{hospital_name: hospital_name_received, hospital_password: hospital_password_received}).then((response : AxiosResponse) => {
        if (response.data != undefined) {
            return response.data;
        }
        return undefined;
    });
    return (await dataPromise).data
}

function generateRandomString(length : number) : string {
    let result = '';
    const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'
    const charactersLength = characters.length
    let counter = 0
    while (counter < length) {
        result += characters.charAt(Math.floor(Math.random()*charactersLength))
        counter = counter+1
    }
    return result;
}

function verifyNIFLetter(nif: string, condicion_extranjero: boolean) : boolean {
    var regexp = new RegExp('[A-Z]')
    var documento : String = condicion_extranjero ? "DNI" : "NIE"
    if (!(regexp.test(nif.charAt(nif.length-1)))) {
        console.log(`Error, no se ha introducido una letra de ${documento} al final del documento`)
        return false;
    }
    if (condicion_extranjero) {
        if (!(regexp.test(nif.charAt(0)))) {
            console.log(`Error, no se ha introducido una letra de ${documento} al principio del documento`)
            return false;
        }
        const letra: string = nif[0]
        nif = nif.slice(1, nif.length)
        nif = tabla_de_extranjeria.get(letra) + nif;
    } 
    const resto_obtenido = parseInt(nif.slice(0,nif.length-1)) % 23;
    if (tabla_de_residuos[resto_obtenido] === nif[nif.length-1]) {
        return true;
    } else {
        console.log(`Letra del ${documento} incorrecta. Compruebe el numero de ${documento} escrito`);
        console.log(`Letra de ${documento} esperada: ` + tabla_de_residuos[resto_obtenido])
        console.log(`Letra de ${documento} obtenida: ` + nif[nif.length-1])
        return false;
    } 
}

/*Options*/

function askForData() {

    /* Variable initialization */
    var firstFileRawData: string = ""
    var secondFileRawData: string = ""
    var hospitalCredentials: string = ""
    var nombre_interesado: string = ""
    var documento_en_uso: string = "";
    var dni_interesado: string = ""

    /*Read file data*/
    try {
        firstFileRawData = fs.readFileSync("first_examination.txt", "utf8");
        secondFileRawData = fs.readFileSync("second_examination.txt", "utf8");
        hospitalCredentials = fs.readFileSync("hospital_credentials.txt", "utf8");
    } catch (err) {
        console.log("No hemos podido encontrar uno de los archivos requeridos: " + err);
        return;
    }
    console.log("Files have been found correctly.");

    /* Read user-provided data */
    rl.question(`Nombre del examinado`, name => {
        nombre_interesado = name
        rl.close();
    });
    rl.question(`Tipo de documento en uso (DNI/NIE)`, name => {
        documento_en_uso = name
        rl.close();
    });
    rl.question(`DNI del examinado (con letra incluida)`, dni => {
        dni_interesado = dni
        verifyNIFLetter(dni_interesado, documento_en_uso === "NIE" ? true : false)
        rl.close();
    });

    /*TODO: Escribir documento de Protección de Datos aquí*/

    /*Send data*/
    var results_reaction_time = firstFileRawData.split("\n")[0]
    var results_first_potentiometer = secondFileRawData.split("\n")[0]
    var results_second_potentiometer = secondFileRawData.split("\n")[1]
    var hospital_alias = hospitalCredentials.split("\n")[0]
    var hospital_pass = hospitalCredentials.split("\n")[1] 
    const data_to_send: PostData = {
        id_received: nombre_interesado.toUpperCase()+"_"+dni_interesado.toUpperCase()+"_"+generateRandomString(20),
        hospital_password: hospital_pass,
        hospital_name: hospital_alias,
        first_exam: results_reaction_time,
        second_exam_first_potentio: results_first_potentiometer,
        second_exam_second_potentio: results_second_potentiometer
    }
    sendData(data_to_send);
}

async function getAllExaminations() {
    var hospitalCredentials : string = ""
    try {
        hospitalCredentials = fs.readFileSync("hospital_credentials.txt", "utf8");
    } catch (err) {
        console.log("No hemos podido encontrar uno de los archivos requeridos: " + err);
        return;
    }
    const hospital_name = hospitalCredentials.split("\n")[0];
    const hospital_password = hospitalCredentials.split("\n")[1]; 
    const received_data = await returnAllExaminations(hospital_name, hospital_password);
    if (received_data === undefined || received_data === null ) {
        console.log("No se han recibido datos correctos");
        return;
    }
    var html_beginning = "<html><head></head><body>"
    var html_table = "<table><tr><th>Datos de paciente</th><th>Resultados primer examen</th><th>Resultados segundo examen 1</th><th>Resultados segundo examen 2</th></tr>"
    for (const test of received_data) {
        html_table = html_table + `<tr><td>${test.id}</td><td>${test.results_reaction_time}</td><td>${test.results_first_potentiometer}</td><td>${test.results_second_potentiometer}</td></tr>`
    }
    var html_end = "</table></body></html>"
    var content = html_beginning + html_table + html_end;
    try {
        fs.writeFileSync('./html_results.html', content);
    } catch (err) {
        console.log("Se ha producido un error al escribir el archivo");
        return;
    } 
}

initializeNIFArray();
console.log("¡Bienvenido/a!");
console.log("*****************************************")
console.log("OPCIONES:")
console.log("1. Agregar una examinacion al sistema")
console.log("2. Obtener todos las examinaciones del hospital")
console.log("3. Salir del programa")