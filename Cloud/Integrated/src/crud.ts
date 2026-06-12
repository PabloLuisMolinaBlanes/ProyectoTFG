import { comparePasswords } from './password';
import prisma from './db'

/*ORM functions*/

/*Devuelve un perfil de usuario según un nombre de hospital*/
export async function getProfile(hospital_name: string) {
    const hospital_received = await prisma.profile.findFirst({
        where: {
            hospital: hospital_name
        } 
    })
    return hospital_received;
} 

/*Crea una examinación según datos recibidos*/
export async function createTest(id_received: string, hospital_password: string, hospital_name: string, first_exam: string, second_exam_first_potentio: string, second_exam_second_potentio: string) {
    const hospital = await getProfile(hospital_name);
    if (hospital == null) {
        return {error: "Wrong password"};
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
export async function getAllTestsPerHospital(hospital_name: string, hospital_password: string) {
    const hospital_received = await getProfile(hospital_name);
    if (hospital_received == null) {
        return {error: "Wrong password"};
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