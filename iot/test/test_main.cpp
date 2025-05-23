#include <Arduino.h>
#include <unity.h>
#include <ArduinoJson.h>

void test_json_parse_example() {
    const char* json = "{\"key\":\"value\"}";
    DynamicJsonDocument doc(1024);
    DeserializationError err = deserializeJson(doc, json);
    TEST_ASSERT_FALSE(err);
    TEST_ASSERT_EQUAL_STRING("value", doc["key"]);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_json_parse_example);
    UNITY_END();
}

void loop() {}
