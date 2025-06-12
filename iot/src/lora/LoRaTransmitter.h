#include <Arduino.h>
#include "SensorData.h"
#include <vector>
#include "../utils/JsonFormatter.h"

using namespace std;

class LoRaTransmitter
{
public:
    LoRaTransmitter();
    bool begin(unsigned long sendInterval);
    bool canSendMessage();
    bool sendMessage();
    void addData(SensorData &data);

private:
    const int csPin = 18;
    const int resetPin = 14;
    const int irqPin = 26;
    const long frequency = 868E6;
    unsigned long lastSendTime;
    unsigned long sendInterval;
    JsonFormatter jsonFormatter;
    vector<SensorData> dataArray;

    String buildMessage();
};