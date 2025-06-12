#include "LoRaReceiver.h"

LoRaReceiver::LoRaReceiver()
{
    initialized = false;
    lastMessage = "";
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
    Serial.println("Récepteur LoRa (Heltec WiFi LoRa 32 V2) initialisé avec succès!");

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

        lastMessage = message;
    }

    return message;
}

void LoRaReceiver::parseAndDisplayJSON(String jsonString)
{
    // Création du document JSON avec une taille appropriée
    DynamicJsonDocument doc(2048);

    // Tentative de parsing du JSON
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error)
    {
        Serial.println("❌ ERREUR DE PARSING JSON:");
        Serial.print("Code d'erreur: ");
        Serial.println(error.c_str());
        return;
    }

    Serial.println("✅ JSON VALIDE - DONNÉES REÇUES:");

    // Vérification que c'est un tableau
    if (!doc.is<JsonArray>())
    {
        Serial.println("❌ Le JSON n'est pas un tableau!");
        return;
    }

    JsonArray sensors = doc.as<JsonArray>();
    Serial.print("Nombre de capteurs: ");
    Serial.println(sensors.size());
    Serial.println();

    // Parcours et affichage de chaque capteur
    int sensorIndex = 1;
    for (JsonObject sensor : sensors)
    {
        Serial.print("--- CAPTEUR ");
        Serial.print(sensorIndex++);
        Serial.println(" ---");
        printSensorData(sensor);
        Serial.println();
    }

    Serial.println("===============================\n");
}

void LoRaReceiver::printSensorData(JsonObject sensor)
{
    // Vérification et affichage de chaque champ
    if (sensor.containsKey("name"))
    {
        Serial.print("📊 Nom: ");
        Serial.println(sensor["name"].as<String>());
    }
    else
    {
        Serial.println("⚠️  Champ 'name' manquant");
    }

    if (sensor.containsKey("value"))
    {
        Serial.print("📈 Valeur: ");
        if (sensor["value"].is<int>())
        {
            Serial.println(sensor["value"].as<int>());
        }
        else if (sensor["value"].is<float>())
        {
            Serial.println(sensor["value"].as<float>(), 2);
        }
        else
        {
            Serial.println(sensor["value"].as<String>());
        }
    }
    else
    {
        Serial.println("⚠️  Champ 'value' manquant");
    }

    if (sensor.containsKey("unit"))
    {
        Serial.print("📏 Unité: ");
        Serial.println(sensor["unit"].as<String>());
    }
    else
    {
        Serial.println("⚠️  Champ 'unit' manquant");
    }

    if (sensor.containsKey("timestamp"))
    {
        Serial.print("🕒 Timestamp: ");
        Serial.println(sensor["timestamp"].as<unsigned long>());

        // Conversion en temps relatif (optionnel)
        unsigned long currentTime = millis();
        unsigned long messageTime = sensor["timestamp"].as<unsigned long>();
        if (currentTime > messageTime)
        {
            Serial.print("   (il y a ");
            Serial.print(currentTime - messageTime);
            Serial.println(" ms)");
        }
    }
    else
    {
        Serial.println("⚠️  Champ 'timestamp' manquant");
    }
}

void LoRaReceiver::loop()
{
    if (isAvailable())
    {
        receive();
    }
}

