#include "LoRaTransmitter.h"
#include "LoRa.h"

LoRaTransmitter::LoRaTransmitter()
{
}

bool LoRaTransmitter::begin(unsigned long delayBetweenMessages)
{
    LoRa.setPins(csPin, resetPin, irqPin);

    if (!LoRa.begin(frequency))
    {
        Serial.println("LoRa initialization failed");
        return false;
    }

    sendInterval = delayBetweenMessages;

    Serial.println("LoRa initialization successful");
    return true;
}

bool LoRaTransmitter::canSendMessage()
{
    unsigned long now = millis();

    return sendInterval < now - lastSendTime && dataArray.size() > 0;
}

String LoRaTransmitter::buildMessage()
{
    String finalMessage = "[";
    for (int i = 0; i < dataArray.size(); i++)
    {
        if (i > 0)
            finalMessage += ",";
        finalMessage += jsonFormatter.dataToJson(&dataArray[i]);
    }
    finalMessage += "]";

    return finalMessage;
}

bool LoRaTransmitter::sendMessage()
{
    String fullMessage = buildMessage();

    LoRa.beginPacket();
    LoRa.print(fullMessage);
    bool hasSucceeded = LoRa.endPacket();

    lastSendTime = millis();
    dataArray.clear();
    Serial.println("-------------------");
    Serial.println("Sending: ");
    Serial.println(fullMessage);
    Serial.println("-------------------");

    return hasSucceeded;
}

void LoRaTransmitter::addData(SensorData &data)
{
    unsigned long now = millis();
    data.timestamp = now;

    dataArray.push_back(data);
}
