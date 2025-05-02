#include <Arduino.h>
#include "./lora/LoRaTransmitter.h"
#include "SensorData.h"

LoRaTransmitter loRaTransmitter;
JsonFormatter jsonFormatter;

void setup()
{
  Serial.begin(115200);
  loRaTransmitter.begin(10000);
}

void loop()
{
  delay(1000);

  if (loRaTransmitter.canSendMessage())
  {
    loRaTransmitter.sendMessage();
  }
}
