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
    for (int i = 0; i < dataArray.size(); i++)
    {
        if (i > 0)
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

void LoRaTransmitter::printMessage(String &message)
{
    String row = "";

    Serial.println("-------------------");
    Serial.println(message);
    Serial.println("Sending: ");

    for (int i = 0; i < message.length(); i++)
    {
        if (message[i] == ARRAY_SPLIT_CHAR)
        {
            Serial.println(row);
            row = "";
        }
        else
        {
            row += message[i];
        }
    }

    if (row.length() > 0)
    {
        Serial.println(row);
    }

    Serial.println("-------------------");
}

bool LoRaTransmitter::sendMessage()
{
    String fullMessage = buildMessage();

    LoRa.beginPacket();
    LoRa.print(fullMessage);
    bool hasSucceeded = LoRa.endPacket();

    lastSendTime = millis();
    dataArray.clear();
    printMessage(fullMessage);

    return hasSucceeded;
}

void LoRaTransmitter::addData(SensorData &data)
{
    unsigned long now = millis();
    data.timestamp = now;

    dataArray.push_back(data);
}
