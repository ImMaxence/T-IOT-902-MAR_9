#include <Arduino.h>
#include "./lora/LoRaTransmitter.h"
#include "./sensorExample/SensorExample.h"
#include "SensorData.h"

LoRaTransmitter loRaTransmitter;
JsonFormatter jsonFormatter;
SensorExample sensorExample;

SensorData data = {
  name : "température",
  value : 1531.3,
  unit : "°C",
  timestamp : 123456
};

SensorData data2 = {
  name : "oussière",
  value : 11.3,
  unit : "m²",
  timestamp : 12365456
};

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
    loRaTransmitter.sendMessage();
  }
}