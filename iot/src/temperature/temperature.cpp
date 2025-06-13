// #include "temperature/temperature.h"

// // ✅ Définition réelle ici
// Adafruit_BMP280 bmp;

// void setupTemperatureSensor() {
//   Serial.begin(115200);

//   if (!bmp.begin(0x76)) {
//     Serial.println("❌ Capteur BMP280 non détecté !");
//     while (1); // Bloque si erreur
//   }

//   Serial.println("✅ BMP280 détecté !");
// }

// void printSensorDataTemp(SensorData data) {
//   Serial.print("📡 ");
//   Serial.print(data.name);
//   Serial.print(" = ");
//   Serial.print(data.value);
//   Serial.print(" ");
//   Serial.print(data.unit);
//   Serial.print(" @ ");
//   Serial.println(data.timestamp);
// }

// void loopTemperatureSensor() {
//   float temperature = bmp.readTemperature();
//   float pressure = bmp.readPressure() / 100.0F;
//   float altitude = bmp.readAltitude(1013.25);
//   long timestamp = millis();

//   SensorData tempData = {"temperature", temperature, "°C", timestamp};
//   SensorData pressData = {"pressure", pressure, "hPa", timestamp};
//   SensorData altData  = {"altitude", altitude, "m", timestamp};

//   printSensorDataTemp(tempData);
//   printSensorDataTemp(pressData);
//   printSensorDataTemp(altData);

//   Serial.println("------");
//   delay(2000);
// }

#include "temperature/temperature.h"

// ✅ Définition réelle ici
Adafruit_BMP280 bmp;

void setupTemperatureSensor() {
  // Serial.begin(115200);

  if (!bmp.begin(0x76)) {
    Serial.println("❌ Capteur BMP280 non détecté !");
    while (1); // Bloque si erreur
  }

  Serial.println("✅ BMP280 détecté !");
}

void printSensorDataTemp(SensorData data) {
  Serial.print("📡 ");
  Serial.print(data.name);
  Serial.print(" = ");
  Serial.print(data.value);
  Serial.print(" ");
  Serial.print(data.unit);
  Serial.print(" @ ");
  Serial.println(data.timestamp);
}

void loopTemperatureSensor() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F;
  float altitude = bmp.readAltitude(1013.25);
  long timestamp = millis();

  SensorData tempData = {"temperature", temperature, "°C", timestamp};
  SensorData pressData = {"pressure", pressure, "hPa", timestamp};
  SensorData altData  = {"altitude", altitude, "m", timestamp};

  printSensorDataTemp(tempData);
  printSensorDataTemp(pressData);
  printSensorDataTemp(altData);

  Serial.println("------");
  delay(2000);
}