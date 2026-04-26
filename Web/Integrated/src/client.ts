/*Imports and definitions*/
import * as crypto from 'crypto';
import axios, { AxiosResponse } from 'axios'
import * as fs from 'fs';
import * as readline from 'readline/promises'
import { exit } from 'process';

/*Variables*/
type nullable<T> = T | null | undefined

var tabla_de_residuos : String[] = [] 

var tabla_de_extranjeria : Map<String, number> = new Map();

const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
});

var key : NonSharedBuffer;
var iv : NonSharedBuffer;

/*Types*/

type PostData = {
    id: string,
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

type DocumentData =  {
    results_reaction_time: string,
    results_first_potentiometer: string,
    results_second_potentiometer: string,
    hospital_alias: string,
    hospital_pass: string
}

type UserData =  {
    nombre_interesado: string,
    nif_interesado: string
}

type OptionToFunction = {
    option_label: string,
    async: boolean,
    function_to_execute: () => void 
} 

/*Auxiliary functions*/

/*Inicializa lookup table para asignar un resto a una letra*/
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

/*
Obtiene clave de encripción e IV de archivo en codificación hexadecimal; si no existen, el programa las genera y almacena en el fichero encryptionparameters.txt.
*/
function initializeEncryptionParameters() {
    try {
        const encryptionparameters = fs.readFileSync(__dirname + '/encryptionparameters.txt', 'utf-8')
        key = Buffer.from(encryptionparameters.split("\n")[0], 'hex')
        iv = Buffer.from(encryptionparameters.split("\n")[1], 'hex')
    } catch (err) {
        key = crypto.randomBytes(32)
        iv = crypto.randomBytes(16)
        const content = `${key.toString('hex')}\n${iv.toString('hex')}`
        fs.writeFileSync(__dirname + '/encryptionparameters.txt', content);
    }
} 

/*Envía petición de mandar datos de examinación*/
async function sendData(data : PostData) : Promise<nullable<Test>>   {
    const dataPromise : AxiosResponse<nullable<Test>> = await axios.post("http://localhost:3000/upload", data);
    return dataPromise.data;
}

/*Envía petición de obtener datos de examinación*/
async function returnAllExaminations(hospital_name_received: string, hospital_password_received: string) : Promise<nullable<Test[]>>  {
    const dataPromise : AxiosResponse<nullable<Test[]>> = await axios.get(`http://localhost:3000/receive?hospital_name=${hospital_name_received}&hospital_password=${hospital_password_received}`);
    return dataPromise.data
}

/*Genera un string aleatorio de longitud length
* Código basado del código original por Roger Knapp y editado por el usuario TylerH (https://stackoverflow.com/a/1349426); Licenciado bajo CC BY-SA 4.0. (https://creativecommons.org/licenses/by-sa/2.5/)
*/
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

/*Verifica que el número de identificación corresponde con la letra proporcionada*/
function verifyNIFLetter(nif: string, condicion_extranjero: boolean) : boolean {
    var regexp = new RegExp('[A-Z]')
    var documento : String = condicion_extranjero ? "NIE" : "DNI"
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

async function userDataLoop(resolve : (value: UserData | PromiseLike<UserData>) => void) {
    var nombre_interesado: string = ""
    var documento_en_uso: string = "";
    var dni_interesado: string = ""
    var accepted: boolean = false;
    while (!accepted) {
        nombre_interesado = ""
        documento_en_uso = ""
        dni_interesado = ""
        /* Read user-provided data */
        nombre_interesado = await rl.question(`Nombre del examinado: `);
        var documento_correcto: boolean = false;
        while (!documento_correcto) {
            documento_en_uso = await rl.question(`Tipo de documento en uso (DNI/NIE): `);
            if (documento_en_uso === "DNI" || documento_en_uso === "NIE") {
                documento_correcto = true;
            } else {
                console.log("Error, tipo de documento invalido")
            } 
        }
        var numero_correcto: boolean = false;
        while (!numero_correcto) {
            dni_interesado = await rl.question(`DNI del examinado (con letra incluida): `);
            if (verifyNIFLetter(dni_interesado, documento_en_uso === "NIE" ? true : false)) {
                numero_correcto = true;
            } else {
                console.log("Error, numero de documento incorrecto; vuelva a indicarlo, por favor");
            }
        }
        var valid_input: boolean = false;
        console.log(`Nombre introducido: ${nombre_interesado}`);
        console.log(`Tipo de documento: ${documento_en_uso}`);
        console.log(`Numero de documento: ${dni_interesado}`);
        while (!valid_input) {    
            var response = await rl.question(`¿Proceder a la subida? (s/n) `);
            if (response === "s") {
                valid_input = true;
                accepted = true;
                var userData: UserData = {nombre_interesado: nombre_interesado, nif_interesado: dni_interesado}; 
                resolve(userData)
            } else if (response === "n") {
                valid_input = true;
                console.log("Vuelva a introducir sus datos de nuevo")
            } else {
                console.log("Error, escriba 's' o 'n', por favor")
            }
        }
    }
}


async function getUserData() : Promise<UserData> {
    return new Promise((resolve) => {userDataLoop(resolve)}); 
}

function parseDocumentData(firstFileRawData: string, secondFileRawData: string, hospitalCredentials: string) : DocumentData {
    var results_reaction_time = firstFileRawData.split("\n")[0]
    var results_first_potentiometer = secondFileRawData.split("\n")[0]
    var results_second_potentiometer = secondFileRawData.split("\n")[1]
    var hospital_alias = hospitalCredentials.split("\n")[0]
    var hospital_pass = hospitalCredentials.split("\n")[1]
    var document_data : DocumentData = {
        results_reaction_time: results_reaction_time,
        results_first_potentiometer: results_first_potentiometer,
        results_second_potentiometer: results_second_potentiometer,
        hospital_alias: hospital_alias,
        hospital_pass: hospital_pass,
    } 
    return document_data
}

async function sendRequest(parsedData: DocumentData, nombre_interesado: string, dni_interesado: string) : Promise<nullable<Test>> {
    const id_to_send = nombre_interesado.toUpperCase()+"_"+dni_interesado.toUpperCase()+"_"+generateRandomString(20)
    const cipher = crypto.createCipheriv('aes256', key, iv)
    const encryptedId = cipher.update(id_to_send, 'utf-8', 'hex') + cipher.final('hex')
    const data_to_send: PostData = {
        id: encryptedId,
        hospital_password: parsedData.hospital_pass,
        hospital_name: parsedData.hospital_alias,
        first_exam: parsedData.results_reaction_time,
        second_exam_first_potentio: parsedData.results_first_potentiometer,
        second_exam_second_potentio: parsedData.results_second_potentiometer
    }
    /*Send and return success*/
    const test_received = await sendData(data_to_send);
    return test_received;
}  

/*Obtiene datos introducidos por el usuario, los valida, y después llama a funciones que envían los datos a la nube.*/
async function askForData() {
    /* Variable initialization */
    var firstFileRawData: string = ""
    var secondFileRawData: string = ""
    var hospitalCredentials: string = ""
    /*Read file data*/
    try {
        firstFileRawData = fs.readFileSync(__dirname + "/first_examination.txt", "utf8");
        secondFileRawData = fs.readFileSync(__dirname + "/second_examination.txt", "utf8");
        hospitalCredentials = fs.readFileSync(__dirname + "/hospital_credentials.txt", "utf8");
    } catch (err) {
        console.log("No hemos podido encontrar uno de los archivos requeridos: " + err);
        return;
    }
    console.log("Files have been found correctly.");
    var userData = await getUserData();
    /*TODO: Escribir documento de Protección de Datos aquí*/
    var parsedData = parseDocumentData(firstFileRawData, secondFileRawData, hospitalCredentials);
    var resultingSent = await sendRequest(parsedData, userData.nombre_interesado, userData.nif_interesado)
    /*Send HTTP request*/
    console.log(`Test with id ${resultingSent?.id} successfully built!`)
    return;
} 

/*Genera el fichero HTML con los datos de cada usuario*/
    /*Resultado de ejemplo (\n solo incluidos con fines de legibilidad)
    * <html>
    *  <head></head>
    *  <body>
    *   <table>
    *    <tr>
    *     <th>Datos de paciente</th>
    *     <th>Resultados primer examen</th>
    *     <th>Resultados segundo examen 1</th>
    *     <th>Resultados segundo examen 2</th>   
    *    </tr>
    *    <tr>
    *     <td><NOMBRE y APELLIDOS>_<NUMERO DOCUMENTO>_<STRING ALEATORIO></td>
    *     <td>0.433,0.788,0.888</td>
    *     <td>0,0,0,0,1,1,2,3,2,1,1,1</td>
    *     <td>599,599,599,598,590,589,589,590,591,585,587,588</td>
    *    </tr>
    *   </table>
    *  </body>
    * </html>
    *
    * */
function generateHTMLString(received_data: nullable<Test[]> ) : string {
    if (received_data === undefined || received_data === null ) {
        console.log("No se han recibido datos correctos");
        return "";
    }
    var html_beginning = "<html><head></head><body>"
    var html_table = "<table><tr><th>Datos de paciente</th><th>Resultados primer examen</th><th>Resultados segundo examen 1</th><th>Resultados segundo examen 2</th></tr>"
    for (const test of received_data) {
        // You have to create the decipher every time you want to use it; otherwise, it throws exception
        const decipher: crypto.Decipheriv = crypto.createDecipheriv('aes256', key, iv)
        const decryptedId = decipher.update(test.id, 'hex', 'utf-8') + decipher.final('utf-8')
        html_table = html_table + `<tr><td>${decryptedId}</td><td>${test.results_reaction_time}</td><td>${test.results_first_potentiometer}</td><td>${test.results_second_potentiometer}</td></tr>`
    }
    var html_end = "</table></body></html>"
    var content = html_beginning + html_table + html_end;
    return content;
} 

/*Obtiene los datos de examinaciones según credenciales y genera archivo .html con datos desencriptados*/ 
async function getAllExaminations() {
    var hospitalCredentials : string = ""
    try {
        hospitalCredentials = fs.readFileSync(__dirname + "/hospital_credentials.txt", "utf8");
    } catch (err) {
        console.log("No hemos podido encontrar uno de los archivos requeridos: " + err);
        return;
    }
    const hospital_name = hospitalCredentials.split("\n")[0];
    const hospital_password = hospitalCredentials.split("\n")[1]; 
    const received_data = await returnAllExaminations(hospital_name, hospital_password);
    var content = generateHTMLString(received_data);
    try {
        fs.writeFileSync(__dirname + '/html_results.html', content);
    } catch (err) {
        console.log("Se ha producido un error al escribir el archivo");
        return;
    }
    console.log("Se han escrito los datos en el fichero html_results.html") 
    return;
}

var optionsToFunctions : OptionToFunction[] =[
    {
    option_label: "1",
    async: true,
    function_to_execute: async () => await askForData()
    },
    {
    option_label: "2",
    async: true,
    function_to_execute: async () => await getAllExaminations()
    },
    {
    option_label: "3",
    async: false,
    function_to_execute: () => process.exit(0)
    },
] 

async function mainLoop() {
    initializeNIFArray()
    while (true) {
        initializeEncryptionParameters()
        var opcion_escogida = ""
        console.log("¡Bienvenido/a!");
        console.log("*****************************************")
        console.log("OPCIONES:")
        console.log("1. Agregar una examinacion al sistema")
        console.log("2. Obtener todos las examinaciones del hospital")
        console.log("3. Salir del programa")
        opcion_escogida = await rl.question("");
        var result : OptionToFunction[] = optionsToFunctions.filter((item) => item.option_label === opcion_escogida)
        if (result.length === 0) {
            console.log("Opcion no reconocida, vuelva a elegir de nuevo");
        } else {
            if (result[0].async == true ) {
                await result[0].function_to_execute(); 
            } else {
                result[0].function_to_execute();
            }
        } 
        /*if (opcion_escogida === "1") {
            askForData()
        } else if (opcion_escogida === "2") {
            getAllExaminations();
        } else if (opcion_escogida === "3") {
            return;
        } else {
            console.log("Opcion no reconocida, vuelva a elegir de nuevo");
        } 
        */
    } 
} 



mainLoop()