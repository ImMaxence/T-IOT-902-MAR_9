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
