#include "LoRaTransmitter.h"
#include "LoRa.h"

LoRaTransmitter::LoRaTransmitter()
{
}

bool LoRaTransmitter::begin(unsigned long delayBetweenMessages)
{
    LoRa.setPins(CS_PIN, RESET_PIN, IRQ_PIN);

    if (!LoRa.begin(FREQUENCY))
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
    String finalMessage = "";
    for(int i = 0;i < dataArray.size();i++)
    {
        if(i > 0)
            finalMessage += ARRAY_SPLIT_CHAR;
            finalMessage += minifyData(dataArray[i]);
    }

    return finalMessage;
}

String LoRaTransmitter::minifyData(SensorData &data)
{
    String finalMessage = "";

    finalMessage += data.name;
    finalMessage += OBJECT_SPLIT_CHAR + data.unit;
    finalMessage += OBJECT_SPLIT_CHAR + (String)data.value;
    finalMessage += OBJECT_SPLIT_CHAR + data.timestamp;

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
