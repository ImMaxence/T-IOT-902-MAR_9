// #include "gps/gps.h"

// void printSensorDataGps(SensorData data) {
//   Serial.print("📡 ");
//   Serial.print(data.name);
//   Serial.print(" = ");
//   Serial.print(data.value, 6);
//   Serial.print(" ");
//   Serial.print(data.unit);
//   Serial.print(" @ ");
//   Serial.println(data.timestamp);
// }

// void setupGPS() {
//   Serial.begin(115200);
//   gpsSerial.begin(9600, SERIAL_8N1, 34, 12); // RX=34, TX=12

//   Serial.println("🛰️ Initialisation du GPS...");
// }

// void loopGPS() {
//   while (gpsSerial.available() > 0) {
//     char c = gpsSerial.read();

//     // 🔍 Affiche les trames brutes NMEA (pour debug)
//     Serial.write(c);

//     gps.encode(c);
//   }

//   // ✅ Affichage de la position si disponible
//   if (gps.location.isValid() && gps.location.isUpdated()) {
//     Serial.println("\n📍 Position GPS trouvée !");

//     long timestamp = millis();
    
//     SensorData gpsLat = {"latitude", gps.location.lat(), "°", timestamp};
//     SensorData gpsLng = {"longitude", gps.location.lng(), "°", timestamp};

//     printSensorDataGps(gpsLat);
//     printSensorDataGps(gpsLng);
//   } else {
//     Serial.println("🔎 Recherche de satellites...");
//   }

//   delay(1000); // Pause pour éviter de spammer
// }
#include "lora/LoRaInstance.h"
#include "gps/gps.h"

TinyGPSPlus gps;
HardwareSerial gpsSerial(1); // Définition réelle ici

void printSensorDataGps(SensorData data) {
  Serial.print("📡 ");
  Serial.print(data.name);
  Serial.print(" = ");
  Serial.print(data.value, 6);
  Serial.print(" ");
  Serial.print(data.unit);
  Serial.print(" @ ");
  Serial.println(data.timestamp);
}

void setupGPS() {
  // Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 34, 12); // RX=34, TX=12
  Serial.println("🛰️ Initialisation du GPS...");
}

void loopGPS() {
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

  delay(1000);
}