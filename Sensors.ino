#include "max6675.h"

MAX6675 thermocouple(6, 5, 4);
unsigned long startTimeB = 0;
int StartingDistance = 0;
bool StartingFlag = true;
float SpringConstant = 2.4;


void GetSensors() {
  unsigned long currentTime = millis();
  if (currentTime - startTimeB >= 250) {
    Temperature = thermocouple.readCelsius();
    startTimeB = currentTime;
  }
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  int duration = pulseIn(3, HIGH);
  int distance = (duration * .0343) / 2;
  if (StartingFlag == true) {
    StartingDistance = distance;
  }
  int DistanceTraveled = StartingDistance - distance;
  PullForce = DistanceTraveled * SpringConstant;
}
