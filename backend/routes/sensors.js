import express from 'express';
import { getSensorById, getSensorMeasurements, postSensorMeasurements } from '../controllers/sensorsController.js';

const router = express.Router();

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
 *           type: string
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
 *           type: string
 *         description: ID du capteur
 *     responses:
 *       200:
 *         description: Mesures du capteur
 *   post:
 *     summary: Enregistrer des données dans Sensor Community
 *     parameters:
 *       - in: path
 *         name: id
 *         required: true
 *         schema:
 *           type: string
 *         description: ID du capteur
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             type: array
 *             items:
 *               type: object
 *               properties:
 *                 name:
 *                   type: string
 *                 value:
 *                   type: number
 *                 unit:
 *                   type: string
 *                 timestamp:
 *                   type: integer
 *           example:
 *             - name: temperature
 *               value: 22.5
 *               unit: C
 *               timestamp: 1718188800
 *     responses:
 *       201:
 *         description: Données enregistrées avec succès
 *       400:
 *         description: Format de données invalide
 */
router.get('/:id/measurements', getSensorMeasurements);
router.post('/:id/measurements', postSensorMeasurements);

export default router;
