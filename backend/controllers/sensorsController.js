import axios from 'axios';

const SENSOR_COMMUNITY_API = 'https://data.sensor.community/airrohr/v1';

export const getSensorById = async (req, res) => {
  try {
    const { id } = req.params;
    const { data } = await axios.get(`${SENSOR_COMMUNITY_API}/sensor/${id}/`);
    res.json(data);
  } catch (error) {
    res.status(500).json({ error: 'Erreur lors de la récupération du capteur.' });
  }
};

export const getSensorMeasurements = async (req, res) => {
  try {
    const { id } = req.params;
    const { data } = await axios.get(`${SENSOR_COMMUNITY_API}/sensor/${id}/`);
    // Les mesures sont dans le champ 'sensordatavalues' de chaque entrée
    const measurements = data.map(entry => ({
      timestamp: entry.timestamp,
      values: entry.sensordatavalues
    }));
    res.json(measurements);
  } catch (error) {
    res.status(500).json({ error: 'Erreur lors de la récupération des mesures.' });
  }
};

export const postSensorMeasurements = async (req, res) => {
  const { id } = req.params;
  const data = req.body;
  if (!Array.isArray(data) || !data.every(item => typeof item.name === 'string' && typeof item.value === 'number' && typeof item.unit === 'string' && typeof item.timestamp === 'number')) {
    return res.status(400).json({ error: 'Format de données invalide.' });
  }
  // Sensor Community n'accepte pas de POST public, donc on simule la réussite
  // Pour un vrai POST, il faudrait une clé API ou endpoint privé, ex :
  // await axios.post(`https://data.sensor.community/airrohr/v1/sensor/${id}/`, data);
  return res.status(201).json({ message: 'Données reçues (simulation, Sensor Community n\'accepte pas de POST public)', data });
};
