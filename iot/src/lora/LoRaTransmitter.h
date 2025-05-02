#include <Arduino.h>
#include "SensorData.h"
#include <vector>
#include "../utils/JsonFormatter.h"

using namespace std;

class LoRaTransmitter {
    public: 
    LoRaTransmitter();
    bool begin(int sendInterval);
    bool canSendMessage();
    bool sendMessage();
    void addData(SensorData& data);
    
    private:
    unsigned long lastSendTime;
    unsigned long sendInterval;
    JsonFormatter jsonFormatter;
    vector<SensorData> dataArray;

    String buildMessage();

};