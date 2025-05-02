#include "LoRaTransmitter.h"
#include "LoRa.h"

LoRaTransmitter::LoRaTransmitter()
{
}

bool LoRaTransmitter::begin(int delayBetweenMessages)
{
    LoRa.setPins(18, 14, 26);

    if (LoRa.begin(868E6))
    {
        Serial.println("LoRa initialization successful");
        return true;
    }
    Serial.println("LoRa initialization failed");
    return false;
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
    bool hasSucceeded = LoRa.endPacket() ? true : false;

    lastSendTime = millis();
    dataArray.clear();

    return hasSucceeded;
}

void LoRaTransmitter::addData(SensorData &data)
{
    unsigned long now = millis();
    data.timestamp = now;

    dataArray.push_back(data);
}
