#include "max6675.h"

MAX6675 thermocouple(6, 5, 4);
unsigned long startTimeB = 0;
int StartingDistance = 0;
bool StartingFlag = true;
float SpringConstant = 2.4;


void GetSensors() {//getting the data form sensors
  unsigned long currentTime = millis();//current time that helps with waiting enough time for the next temperature reading
  if (currentTime - startTimeB >= 250) {//we are reading the temperature every 250 ms since the sensor cant handle less time
    Temperature = thermocouple.readCelsius();
    startTimeB = currentTime;
  }
  //turning the ultra sonic sensor on
  digitalWrite(2, LOW);
  delayMicroseconds(2);
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
  //reading and calculating the distance it has travleed
  int duration = pulseIn(3, HIGH);
  int distance = (duration * .0343) / 2;
  if (StartingFlag == true) {//setting the first distance that is then the engine is not working
    StartingDistance = distance;
  }
  //calculating the force  that is pulled form the springs
  int DistanceTraveled = StartingDistance - distance;
  PullForce = DistanceTraveled * SpringConstant;
  PullForce = PullForce / 2;//deviding it by 2 since there are 2 springs
}
