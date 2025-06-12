import express from 'express';
import { getSensorById, getSensorMeasurements } from '../controllers/sensorsController.js';

const router = express.Router();

/**
 * @swagger
 * /sensors:
 *   get:
 *     summary: Liste tous les capteurs Sensor Community
 *     responses:
 *       200:
 *         description: Liste des capteurs
 */
router.get('/', getSensors);

/**
 * @swagger
 * /sensors/{id}:
 *   get:
 *     summary: Détail d'un capteur
 *     parameters:
 *       - in: path
 *         name: id
 *         required: true
 *         schema:
 *           type: integer
 *         description: ID du capteur
 *     responses:
 *       200:
 *         description: Détail du capteur
 */
router.get('/:id', getSensorById);

/**
 * @swagger
 * /sensors/{id}/measurements:
 *   get:
 *     summary: Mesures d'un capteur
 *     parameters:
 *       - in: path
 *         name: id
 *         required: true
 *         schema:
 *           type: integer
 *         description: ID du capteur
 *     responses:
 *       200:
 *         description: Mesures du capteur
 */
router.get('/:id/measurements', getSensorMeasurements);

export default router;
