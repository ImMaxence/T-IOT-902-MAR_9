#include <Arduino.h>
#include "sensorData/sensorData.h"
#include <vector>
#include "jsonFormatter/jsonFormatter.h"

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
    unsigned long lastSendTime;
    unsigned long sendInterval;
    JsonFormatter jsonFormatter;
    vector<SensorData> dataArray;

    String buildMessage();
    void printMessage(String &message);
    String minifyData(SensorData &data);
};