import * as crypto from 'crypto';
import * as fs from 'fs'
const message = "I like trains"
var key : NonSharedBuffer;
var iv : NonSharedBuffer;
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

const cipher = crypto.createCipheriv('aes256', key, iv)

const encryptedmessage = cipher.update(message, 'utf-8', 'hex') + cipher.final('hex')

console.log(`Encrypted message ${encryptedmessage}`)

const decipher = crypto.createDecipheriv('aes256', key, iv)

const decryptedmessage = decipher.update(encryptedmessage, 'hex', 'utf-8') + decipher.final('utf-8')

console.log(`Decrypted message ${decryptedmessage}`)