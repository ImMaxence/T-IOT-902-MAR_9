#include <Arduino.h>
#include "./lora/LoRaTransmitter.h"
#include "./sensorExample/SensorExample.h"
#include "SensorData.h"

LoRaTransmitter loRaTransmitter;
JsonFormatter jsonFormatter;
SensorExample sensorExample;

void setup()
{
  Serial.begin(115200);
  loRaTransmitter.begin(3000);
}

void loop()
{
  delay(1000);
  sensorExample.readSensor();
  if (loRaTransmitter.canSendMessage())
  {
    Serial.println(loRaTransmitter.sendMessage() ? "message envoyé" : "error");
  }
}
