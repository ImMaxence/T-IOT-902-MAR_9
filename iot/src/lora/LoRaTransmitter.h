#include <Arduino.h>
#include "SensorData.h"
#include <vector>
#include "../utils/JsonFormatter.h"

using namespace std;

#define CS_PIN 18
#define IRQ_PIN 14
#define RESET_PIN 26
#define FREQUENCY 868E6
#define ARRAY_SPLIT_CHAR '_'
#define OBJECT_SPLIT_CHAR '|'

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
    String minifyData(SensorData &data);
};