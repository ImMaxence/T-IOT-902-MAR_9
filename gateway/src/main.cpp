#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Started");
  sleep(3000);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}