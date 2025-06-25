#ifndef HTTPS_TRANSMITTER_H
#define HTTPS_TRANSMITTER_H

#include <Arduino.h>
#include <vector>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

using namespace std;

#define HTTPS_SSID "Livebox-7DF0"
#define HTTPS_PASSWORD "wzWPoA3Q4qwUxAp4KK"
#define HTTPS_SERVER_URL "https://to-delete-production.up.railway.app/api/sensors"
#define HTTPS_ROOT_CA_CERTIFICATE "-----BEGIN CERTIFICATE-----\nVotre certificat racine ici\n-----END CERTIFICATE-----\n"

#define ARRAY_SPLIT_CHAR '_'
#define OBJECT_SPLIT_CHAR '|'

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
