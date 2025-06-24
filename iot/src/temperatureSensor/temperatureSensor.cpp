#include "temperatureSensor/temperatureSensor.h"
#include "lora/LoRaInstance.h"

TemperatureSensor::TemperatureSensor() {}

void TemperatureSensor::setup()
{
  if (!bmp.begin(0x76))
  {
    Serial.println("❌ Capteur BMP280 non détecté !");
    while (1)
      ; // Bloque si erreur
  }

  Serial.println("✅ BMP280 détecté !");
}

void TemperatureSensor::printSensorData(SensorData data)
{
  Serial.print("📡 ");
  Serial.print(data.name);
  Serial.print(" = ");
  Serial.print(data.value);
  Serial.print(" ");
  Serial.print(data.unit);
  Serial.print(" @ ");
  Serial.println(data.timestamp);
}

void TemperatureSensor::readSensorData()
{
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;
  float altitude = bmp.readAltitude(1013.25);
  long timestamp = millis();

  SensorData tempData = {"temperature", temperature, "°C", 0};
  SensorData pressData = {"pressure", pressure, "hPa", 0};
  SensorData altData = {"altitude", altitude, "m", 0};

  // Envoi LoRa
  loRaTransmitter.addData(tempData);
  loRaTransmitter.addData(pressData);
  loRaTransmitter.addData(altData);

  // printSensorData(tempData);
  // printSensorData(pressData);
  // printSensorData(altData);

  // Serial.println("------");
}
