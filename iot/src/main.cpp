#include <Arduino.h>
#include <Wire.h>
#include "./lora/LoRaTransmitter.h"
#include "./sensorExample/SensorExample.h"
#include "SensorData.h"
#include "temperatureSensor/temperatureSensor.h"
#include "gpsSensor/gpsSensor.h"

LoRaTransmitter loRaTransmitter;

GPSSensor gpsSensor;
TemperatureSensor temperatureSensor;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Wire.begin(21, 22);
  Serial.println("▶ setup démarré");

  loRaTransmitter.begin(3000);
  gpsSensor.setup();
  temperatureSensor.setup();
}

void loop()
{
  temperatureSensor.readSensorData();
  gpsSensor.readSensorData();
  if (loRaTransmitter.canSendMessage())
  {
    Serial.println(loRaTransmitter.sendMessage() ? "-----------message envoyé-----------" : "-----------error lors de l'envoi-----------");
  }
  delay(1000);
}
