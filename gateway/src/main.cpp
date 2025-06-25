#include <Arduino.h>
#include "loRaReceiver/loRaReceiver.h"
#include "httpsTransmitter/httpsTransmitter.h"

LoRaReceiver receiver;
HttpsTransmitter transmitter;

String receivedMessage = "";

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("=== DÉMARRAGE DU RÉCEPTEUR LORA ===");

    if (!receiver.begin())
    {
        Serial.println("Échec de l'initialisation du récepteur LoRa");
        while (1)
        {
            delay(1000);
        }
    }

    Serial.println("Récepteur prêt, en attente de messages...\n");

    transmitter.begin();
}

void loop()
{
    receivedMessage = receiver.receive();
    bool result = transmitter.sendMessage(receivedMessage);
    delay(100);
}
