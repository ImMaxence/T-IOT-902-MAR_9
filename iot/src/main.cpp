#include <TinyGPS++.h>

TinyGPSPlus gps;
HardwareSerial gpsSerial(1); // UART1

struct SensorData {
  String name;
  float value;
  String unit;
  long timestamp;
};

void printSensorData(SensorData data) {
  Serial.print("📡 ");
  Serial.print(data.name);
  Serial.print(" = ");
  Serial.print(data.value, 6);
  Serial.print(" ");
  Serial.print(data.unit);
  Serial.print(" @ ");
  Serial.println(data.timestamp);
}

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 34, 12); // RX=34, TX=12

  Serial.println("🛰️ Initialisation du GPS...");
}

void loop() {
  while (gpsSerial.available() > 0) {
    char c = gpsSerial.read();

    // 🔍 Affiche les trames brutes NMEA (pour debug)
    Serial.write(c);

    gps.encode(c);
  }

  // ✅ Affichage de la position si disponible
  if (gps.location.isValid() && gps.location.isUpdated()) {
    Serial.println("\n📍 Position GPS trouvée !");

    long timestamp = millis();
    
    SensorData gpsLat = {"latitude", gps.location.lat(), "°", timestamp};
    SensorData gpsLng = {"longitude", gps.location.lng(), "°", timestamp};

    printSensorData(gpsLat);
    printSensorData(gpsLng);
  } else {
    Serial.println("🔎 Recherche de satellites...");
  }

  delay(1000); // Pause pour éviter de spammer
}

// #include <Adafruit_BMP280.h> // BMP280 I2C

// Adafruit_BMP280 bmp; // I2C par défaut (SDA=21, SCL=22)

// struct SensorData {
//   String name;
//   float value;
//   String unit;
//   long timestamp;
// };

// void setup() {
//   Serial.begin(115200);

//   // Initialisation BMP280
//   if (!bmp.begin(0x76)) { // Adresse I2C par défaut 0x76 ou 0x77
//     Serial.println("❌ Capteur BMP280 non détecté !");
//     while (1); // Boucle infinie si erreur
//   }

//   Serial.println("✅ BMP280 détecté !");
// }

// void printSensorData(SensorData data) {
//   Serial.print("📡 ");
//   Serial.print(data.name);
//   Serial.print(" = ");
//   Serial.print(data.value);
//   Serial.print(" ");
//   Serial.print(data.unit);
//   Serial.print(" @ ");
//   Serial.println(data.timestamp);
// }

// void loop() {
//   float temperature = bmp.readTemperature();
//   float pressure = bmp.readPressure() / 100.0F;
//   float altitude = bmp.readAltitude(1013.25);
//   long timestamp = millis();

//   SensorData tempData = {"temperature", temperature, "°C", timestamp};
//   SensorData pressData = {"pressure", pressure, "hPa", timestamp};
//   SensorData altData  = {"altitude", altitude, "m", timestamp};

//   // Exemple d'affichage
//   printSensorData(tempData);
//   printSensorData(pressData);
//   printSensorData(altData);

//   Serial.println("------");

//   delay(2000);
// }