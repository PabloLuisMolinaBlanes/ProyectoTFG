var tabla_de_residuos : String[] = [] 

var tabla_de_extranjeria : Map<String, number> = new Map();

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

/*Genera un string aleatorio de longitud length
* Código basado del código original por Roger Knapp y editado por el usuario TylerH (https://stackoverflow.com/a/1349426); Licenciado bajo CC BY-SA 4.0. (https://creativecommons.org/licenses/by-sa/2.5/)
*/
export function generateRandomString(length : number) : string {
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
export function verifyNIFLetter(nif: string, condicion_extranjero: boolean) : boolean {
    if (tabla_de_residuos.length === 0) {
        initializeNIFArray()
    }
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