import { PrismaClient } from "@prisma/client";
import { PrismaMariaDb } from "@prisma/adapter-mariadb";

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

export default prisma