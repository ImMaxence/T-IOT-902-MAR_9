#include <Arduino.h>
#include <Wire.h>
#include "./lora/LoRaTransmitter.h"
#include "./sensorExample/SensorExample.h"
#include "SensorData.h"
#include "temperature/temperature.h"
#include "gps/gps.h"

LoRaTransmitter loRaTransmitter;
JsonFormatter jsonFormatter;
SensorExample sensorExample;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Wire.begin(21, 22);
  Serial.println("▶ setup démarré");

  // loRaTransmitter.begin(3000);
  setupGPS();
  // setupTemperatureSensor();
}

void loop()
{
  loopGPS();
  // loopTemperatureSensor();
  // delay(1000);
  // sensorExample.readSensor();
  // if (loRaTransmitter.canSendMessage())
  // {
  //   Serial.println(loRaTransmitter.sendMessage() ? "message envoyé" : "error");
  // }
}
