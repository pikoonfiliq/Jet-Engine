extern int Mode = 0;

extern int Temperature = 0;
extern int Thrust = 0;
extern int AirVal = 0;
extern int GasVal = 0;
extern bool Start = false;
extern int Status = 0;
extern int SpeedVal = 0;


void setup() {
  DisplayBeninging();
  ChoseMode();
}

void loop() {
  GetControls();
  GetSensors();
  DisplayMainMenu();
  ControlEngine();
}
