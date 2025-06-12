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

// Envoi direct à Sensor Community (endpoint officiel)
export const postSensorMeasurements = async (req, res) => {
  // On accepte un body de type :
  // [
  //   { name: 'P1', value: 66.04, unit: 'µg/m³', timestamp: 1718190000 },
  //   ...
  // ]
  // et un sensorId (en paramètre d'URL ou dans le body), xPin (dans le body, optionnel)
  const { id: sensorIdParam } = req.params;
  const { sensorId: sensorIdBody, xPin = "1" } = req.body;
  const dataArray = Array.isArray(req.body) ? req.body : req.body.data;
  const sensorId = sensorIdParam || sensorIdBody || "esp8266-1234567890";

  if (!Array.isArray(dataArray) || !sensorId) {
    return res.status(400).json({ error: 'Format de données invalide. Attendu : tableau [{ name, value, unit, timestamp }]' });
  }

  // Transformation en format Sensor Community
  const sensordatavalues = dataArray.map(item => ({
    value_type: item.name,
    value: String(item.value)
  }));

  const URL_ENDPOINT = "https://api.sensor.community/v1/";
  const headers = {
    "X-Sensor": sensorId,
    "X-Pin": xPin,
    "Content-Type": "application/json"
  };
  const data = {
    software_version: "0.0.1",
    sensordatavalues
  };
  try {
    const response = await axios.post(URL_ENDPOINT, data, { headers });
    return res.status(response.status).json({ message: "Data envoyée à Sensor Community", status: response.status });
  } catch (err) {
    return res.status(err.response?.status || 500).json({ error: err.response?.data || err.message });
  }
};
