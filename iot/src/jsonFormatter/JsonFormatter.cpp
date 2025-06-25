#include "jsonFormatter/jsonFormatter.h"
#include <ArduinoJson.h>

JsonFormatter::JsonFormatter() {

};

String JsonFormatter::dataToJson(SensorData *data)
{
    JsonDocument json;
    String serializedJson;

    json["name"] = data->name;
    json["value"] = data->value;
    json["unit"] = data->unit;
    json["timestamp"] = data->timestamp;

    serializeJson(json, serializedJson);

    return serializedJson;
}
