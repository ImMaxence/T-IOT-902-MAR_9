#ifndef HTTPSTRANSMITTER_H
#define HTTPSTRANSMITTER_H

#include <Arduino.h>
#include <SensorData.h>
#include <vector>

using namespace std;

class HttpsTransmitter
{
private:
    String buildMessage(vector<SensorData> &message);

public:
    HttpsTransmitter();
    ~HttpsTransmitter();

    bool begin();
    bool sendMessage(vector<SensorData> &message);
};

#endif