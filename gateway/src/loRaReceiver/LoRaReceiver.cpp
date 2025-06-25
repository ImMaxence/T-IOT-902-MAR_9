#include "loRaReceiver/loRaReceiver.h"
#include <vector>
#include <sensorData/sensorData.h>

using namespace std;

LoRaReceiver::LoRaReceiver()
{
    initialized = false;
}

LoRaReceiver::~LoRaReceiver()
{
}

bool LoRaReceiver::begin()
{
    Serial.println("Initialisation du récepteur");

    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

    if (!LoRa.begin(LORA_FREQUENCY))
    {
        Serial.println("Erreur d'initialisation du récepteur");
        return false;
    }

    LoRa.setSpreadingFactor(7);
    LoRa.setSignalBandwidth(125E3);
    LoRa.setCodingRate4(5);
    LoRa.enableCrc();

    initialized = true;
    Serial.println("Récepteur initialisé avec succès");

    return true;
}

bool LoRaReceiver::isAvailable()
{
    if (!initialized)
        return false;
    return LoRa.parsePacket() > 0;
}

String LoRaReceiver::receive()
{
    int packetSize = LoRa.parsePacket();
    String message = "";

    if (packetSize)
    {
        Serial.println("-------------------");
        Serial.println("message reçu");
        Serial.print("Taille: ");
        Serial.print(packetSize);
        Serial.println(" bytes");

        while (LoRa.available())
        {
            message += (char)LoRa.read();
        }

        Serial.print("Contenu: ");
        Serial.println(message);
        Serial.println("-------------------");
    }

    return message;
}

vector<SensorData> LoRaReceiver::decodeMessage(String &encodedMessage)
{
    vector<SensorData> result;
    vector<String> parsedData = splitMessageArray(encodedMessage);

    for (int i = 0; i < parsedData.size(); i++)
    {
        result.push_back(parseObject(parsedData[i]));
    }

    return result;
}

vector<String> LoRaReceiver::splitMessageArray(String &encodedMessage)
{
    vector<String> parsedData;
    String dataObject = "";

    for (size_t i = 0; i < encodedMessage.length(); i++)
    {
        if (encodedMessage[i] == ARRAY_SPLIT_CHAR)
        {
            parsedData.push_back(dataObject);
            dataObject = "";
        }
        else
        {
            dataObject += encodedMessage[i];
        }
    }

    parsedData.push_back(dataObject);

    return parsedData;
}

SensorData LoRaReceiver::parseObject(String &object)
{
    SensorData result;
    vector<String> splittedObject;
    String encodedObject = "";

    for (size_t i = 0; i < object.length(); i++)
    {
        if (object[i] == OBJECT_SPLIT_CHAR)
        {
            splittedObject.push_back(object);
            object = "";
        }
        else
        {
            object += object[i];
        }
    }

    result.name = splittedObject[0];
    result.value = splittedObject[1].toFloat();
    result.unit = splittedObject[2];
    result.timestamp = splittedObject[3].toInt();

    return result;
}

void LoRaReceiver::loop()
{
    String encodedMessage = "";

    if (isAvailable())
    {
        encodedMessage = receive();
    }

    if (encodedMessage == "")
        return;

    vector<SensorData> decodedMessage = decodeMessage(encodedMessage);
}
