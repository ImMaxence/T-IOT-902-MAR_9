#ifndef LORARECEIVER_H
#define LORARECEIVER_H

#include <Arduino.h>
#include <LoRa.h>
#include <ArduinoJson.h>

#define LORA_SS      18
#define LORA_RST     14
#define LORA_DIO0    26
#define LORA_FREQUENCY 868E6

class LoRaReceiver {
private:
    bool initialized;
    String lastMessage;
    
    void printSensorData(JsonObject sensor);
    void parseAndDisplayJSON(String jsonString);

public:
    LoRaReceiver();
    ~LoRaReceiver();
    
    bool begin();
    bool isAvailable();
    String receive();
    void loop();
};

#endif
