#include <Arduino.h>
#include "./loRaReceiver/LoRaReceiver.h"

LoRaReceiver receiver;

void setup() {
    Serial.begin(115200);
    delay(2000);
    
    Serial.println("=== DÉMARRAGE DU RÉCEPTEUR LORA ===");
    
    if (!receiver.begin()) {
        Serial.println("Échec de l'initialisation du récepteur LoRa!");
        while (1) {
            delay(1000);
        }
    }
    
    Serial.println("Récepteur prêt, en attente de messages...\n");
}

void loop() {
    receiver.receive();
    delay(100); // Petite pause pour éviter de surcharger le CPU
}
