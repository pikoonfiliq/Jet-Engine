#include <Servo.h>
Servo AirServo;
Servo GasServo;


void ChoseMode() {

  int Val = map(analogRead(A2), 0, 1020, 0, 100); //reading the potenciometer and mapping it 0-100
  int oldVal = Val; // helper variable so we now wich direction is the potenciometer moving (basicaly making a budget rotary encoder)
  int direction = 0; // the direction of the potenciometer
  int Options = 2;  // maximum options to choose between
  while (1) {
    Val = map(analogRead(A2), 0, 1020, 0, 50);//reading the potenciometer and mapping it 0-50
    if (oldVal < Val) {
      //direction is up
      direction = 1;
    } else if (oldVal > Val) {
      //direction is up
      direction = -1;
    } else {
      //no direction
      direction = 0;
    }
    oldVal = Val;
    Mode += direction;// getting the current position
    if (Mode < 0) {//checks for the position limits
      Mode = 0;
    } else if (Mode >= Options) {
      Mode = Options - 1;
    }
    if (digitalRead(12) == HIGH) {//if the select button is pressed we exit
      DisplayChooseMenu(1);
      return;
    }
    DisplayChooseMenu(0);
  }
}

void GetControls() {
  if (!Start) {//waiting for the button to be pressed so we can start
    if (digitalRead(12) == HIGH) {
      Start = true;
      return;
    }
  }
  switch (Mode) {// controls based on the chosen mode
    case 0:
      GetControlsMan();
      break;
    case 1:
      GetControlsAut();
      break;
    default:
      //error
      break;
  }
}

void GetControlsMan() {//reading the 2 potenciometers that control gas and air flow
  GasVal = map(analogRead(A2), 0, 1020, 0, 100);
  AirVal = map(analogRead(A3), 0, 1020, 0, 100);
}
void GetControlsAut() {//reading the 1 potenciometers that control speed of the engine (this engine is controlled only with the air)
  SpeedVal = map(analogRead(A3), 0, 1020, 0, 100);
}

void ControlEngine() {// controling the engine based on the chosen mode
  switch (Mode) {
    case 0:
      ControlEngineMan();
      break;
    case 1:
      ControlEngineAut();
      break;
    default:
      //error
      break;
  }
}

void PinsINIT() {//initing the pins
  GasServo.attach(9);//servo 1
  AirServo.attach(10);//sevor 2
  GasServo.write(0);
  AirServo.write(0);
  pinMode(12, INPUT);//Sellect button
  pinMode(7, OUTPUT);//relay pin
  pinMode(2, OUTPUT); //trigger pin
	pinMode(3, INPUT);  //echo pin

}

void ControlEngineMan() {//basic manual controls
  if (digitalRead(12) == HIGH) {
    Stage = 2;
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  int GasTmpVal = map(GasVal, 0, 100, 0, 180);
  GasServo.write(GasTmpVal);
  int AirTmpVal = map(AirVal, 0, 100, 0, 180);
  AirServo.write(AirTmpVal);
}

unsigned long startTime = 0;  // variable to store the start time of each timer
int currentStep = 0;          // variable to keep track of the current step
bool speedValLocked = false;  // locks the speed so that the engine doesnt stop because the knob is too low

void ControlEngineAut() {
  unsigned long currentTime = millis();
  if (Stage == 0) {//waiting for the start button
    if (digitalRead(12) == HIGH) {
      Stage = 1;
    }
  } else if (Stage == 1) {// starting up stage
    if (currentStep == 0) {
      // start air at 50 percent
      AirServo.write(90);
      GasServo.write(180);
      startTime = currentTime;
      currentStep++;
    } else if (currentStep == 1 && currentTime - startTime >= 2000) {
      // gas at 100 percent after 2 seconds
      startTime = currentTime;  // store the start time of the next timer
      currentStep++;
    } else if (currentStep == 2 && currentTime - startTime >= 1000) {
      // light it up for 1 second
      digitalWrite(7, HIGH);
      // Reset the pin after 1 second
      startTime = currentTime;
      currentStep++;
    } else if (currentStep == 3 && currentTime - startTime >= 1000) {
      // Turn off the light after 1 second
      digitalWrite(7, LOW);
      // Move to the next Stage
      Stage = 2;
      startTime = currentTime;
    }
  } else if (Stage == 2) {//the engine is on
    if (!speedValLocked && SpeedVal < 80) {
      SpeedVal = 80;
    } else {
      speedValLocked = true;
    }
    if (currentTime - startTime <= 60000) {// it will run for 60 secounds 
      int SpeedValTmpVal = map(SpeedVal, 0, 100, 0, 180);
      AirServo.write(SpeedValTmpVal);
    } else {
      Stage = 3;
    }
  }
  else if (Stage == 3) {// the engine is cooling off until its below 50 degrees
    if (Temperature > 50) {
      AirServo.write(180);
      GasServo.write(0);
    } else {
      Stage = 0;
    }
  }
}
