#include "max6675.h"

MAX6675 thermocouple(6, 5, 4);
unsigned long startTimeB = 0;
void GetSensors() {
  unsigned long currentTime = millis();
  if (currentTime - startTimeB >= 250) {
    Temperature = thermocouple.readCelsius();
    Serial.println(thermocouple.readCelsius());
    startTimeB = currentTime;
  }
}
