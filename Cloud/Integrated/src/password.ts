import bcrypt from 'bcrypt'


export function comparePasswords(password : string, passwordHash : string) : Promise<boolean> {
    return bcrypt.compare(password, passwordHash)
}

/*Genera un hash bcrypt2 de la clave enviada; con 10 iteraciones de semilla*/
export async function hashPassword(password : string) : Promise<string> {
    return await bcrypt.hash(password, 10)
}