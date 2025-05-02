#include <Arduino.h>
#include "./lora/LoRaTransmitter.h"
#include "SensorData.h"

LoRaTransmitter loRaTransmitter;
JsonFormatter jsonFormatter;

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
  loRaTransmitter.begin(1000);
}

void loop()
{
  delay(1000);
  loRaTransmitter.addData(data);
  loRaTransmitter.addData(data2);

  if (loRaTransmitter.canSendMessage())
  {
    loRaTransmitter.sendMessage();
  }
}