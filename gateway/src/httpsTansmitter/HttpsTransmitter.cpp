#include "HttpsTransmitter.h"
using namespace std;

HttpsTransmitter::HttpsTransmitter()
{
}

HttpsTransmitter::~HttpsTransmitter()
{
}

bool HttpsTransmitter::begin()
{
    return true;
}

String HttpsTransmitter::buildMessage(vector<SensorData> &message)
{
    return "";
}

bool HttpsTransmitter::sendMessage(vector<SensorData> &message)
{
    return true;
}