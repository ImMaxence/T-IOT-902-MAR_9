import express from 'express';
import cors from 'cors';
import dotenv from 'dotenv';
import sensorsRouter from './routes/sensors.js';
import setupSwagger from './swagger.js';

dotenv.config();

const app = express();
app.use(cors());
app.use(express.json());

app.use('/sensors', sensorsRouter);

setupSwagger(app);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}`);
});