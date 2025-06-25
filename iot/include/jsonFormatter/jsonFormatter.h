#include "sensorData/sensorData.h"
#include <Arduino.h>

class JsonFormatter
{
public:
    JsonFormatter();
    String dataToJson(SensorData *data);
};