#ifndef HTTPS_TRANSMITTER_H
#define HTTPS_TRANSMITTER_H

#include <Arduino.h>
#include <vector>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

using namespace std;

class HttpsTransmitter
{
private:
    WiFiClientSecure wifiClient;
    HTTPClient https;

    String buildMessage(String message);
    bool connectToWiFi();
    bool isConnectedToWiFi();

public:
    HttpsTransmitter();
    ~HttpsTransmitter();

    bool begin();
    bool sendMessage(String &message);
};

#endif
