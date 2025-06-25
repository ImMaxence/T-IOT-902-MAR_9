#ifndef LORARECEIVER_H
#define LORARECEIVER_H

#include <Arduino.h>
#include <vector>
#include <LoRa.h>
#include <ArduinoJson.h>
#include <sensorData/sensorData.h>

using namespace std;

#define LORA_SS      18
#define LORA_RST     14
#define LORA_DIO0    26
#define LORA_FREQUENCY 868E6
#define ARRAY_SPLIT_CHAR '_'
#define OBJECT_SPLIT_CHAR '|'

class LoRaReceiver {
private:
    bool initialized;
    vector<SensorData> lastMessage;
    
    vector<SensorData> decodeMessage(String& encodedMessage);
    vector<String> splitMessageArray(String& encodedMessage);
    SensorData parseObject(String& object);

public:
    LoRaReceiver();
    ~LoRaReceiver();
    
    bool begin();
    bool isAvailable();
    String receive();
    void loop();
};

#endif
