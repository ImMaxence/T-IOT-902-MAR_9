#include "gpsSensor/gpsSensor.h"
#include "lora/LoRaInstance.h"

GPSSensor::GPSSensor() : gpsSerial(1) {}

void GPSSensor::printSensorDataGps(SensorData data) {
  Serial.print("📡 ");
  Serial.print(data.name);
  Serial.print(" = ");
  Serial.print(data.value, 6);
  Serial.print(" ");
  Serial.print(data.unit);
  Serial.print(" @ ");
  Serial.println(data.timestamp);
}

void GPSSensor::setup() {
  gpsSerial.begin(9600, SERIAL_8N1, 34, 12); // RX=34, TX=12
  Serial.println("🛰️ Initialisation du GPS...");
}

void GPSSensor::readSensorData() {
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();
    Serial.write(c); // Trame NMEA brute
    gps.encode(c);
  }

  if (gps.location.isValid() && gps.location.isUpdated()) {
    Serial.println("\n📍 Position GPS trouvée !");
    long timestamp = millis();
    SensorData gpsLat = {"latitude", (float)gps.location.lat(), "°", 0};
    SensorData gpsLng = {"longitude", (float)gps.location.lng(), "°", 0};

    loRaTransmitter.addData(gpsLat);
    loRaTransmitter.addData(gpsLng);

    printSensorDataGps(gpsLat);
    printSensorDataGps(gpsLng);
  } else {
    Serial.println("🔎 Recherche de satellites...");
  }
}
