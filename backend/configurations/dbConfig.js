import { Sequelize } from "sequelize"
import dotenv from "dotenv"

dotenv.config()

const sequelize = new Sequelize(
    process.env.POSTGRES_DB,
    process.env.POSTGRES_USER,
    process.env.POSTGRES_PASSWORD,
    {
        host: process.env.POSTGRES_HOST,
        port: process.env.POSTGRES_PORT,
        dialect: "postgres",
        logging: false,
    }
);

sequelize
    .authenticate()
    .then(() => {
        console.log("Connection to PostgreSQL has been established successfully ✅")
    })
    .catch((e) => {
        console.error("❌ Unable to connect to the database : ", e)
    });

export default sequelize