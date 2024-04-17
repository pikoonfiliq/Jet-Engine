extern int Mode = 0; //Saves if the mode is automatic or manual
//sensor readings
extern int Temperature = 0;
extern float PullForce = 0;
//control variables
extern int AirVal = 0;
extern int GasVal = 0;
extern int SpeedVal = 0;
//variables and flags for automatic mode(they are here and made global so that the display functions can read them)
extern bool Start = false;
extern int Stage = 0;


void setup() {
  PinsINIT();
  DisplayBeninging();
  ChoseMode();
}

void loop() {
  GetControls();
  GetSensors();
  DisplayMainMenu();
  ControlEngine();
}
