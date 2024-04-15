
void ChoseMode() {
  pinMode(12, INPUT);
  int Val = map(analogRead(A2), 0, 1023, 0, 100);
  int oldVal = Val;
  int direction = 0;
  int Options = 2;
  while (1) {
    Val =  map(analogRead(A2), 0, 1023, 0, 50);
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
    Mode += direction;
    if (Mode < 0) {
      Mode = 0;
    } else if (Mode >= Options) {
      Mode = Options - 1;
    }
    if (digitalRead(12) == HIGH) {
      DisplayChooseMenu(1);
      return;
    }
    DisplayChooseMenu(0);
  }
}

void GetControls() {
  if (!Start) {
    if (digitalRead(12) == HIGH) {
      Start = true;
      return;
    }
  }
  switch (Mode)
  {
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

void GetControlsMan() {
  int GasVal = map(analogRead(A2), 0, 1023, 0, 100);
  int AirVal = map(analogRead(A3), 0, 1023, 0, 100);

}
void GetControlsAut() {
  int SpeedVal = map(analogRead(A2), 0, 1023, 0, 100);
  
}

void ControlEngine(){
  switch (Mode)
  {
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

void ControlEngineMan(){
  
  }

void ControlEngineAut(){
  
  }
