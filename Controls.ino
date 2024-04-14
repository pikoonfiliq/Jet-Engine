
void ChoseMode(){
  pinMode(12, INPUT);
  int Val = map(analogRead(A2), 0, 1023, 0, 100);
  int oldVal = Val;
  int direction = 0;
  int Options = 2;
  while(1){
    Val =  map(analogRead(A2), 0, 1023, 0, 50);
    Serial.println(Val);
    if(oldVal < Val){
      //direction is up
      direction = 1;
    }else if(oldVal > Val){
      //direction is up
      direction = -1;
    }else {
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
    if(digitalRead(12)== HIGH){
      DisplayChooseMenu(1);
      return;
    }
    DisplayChooseMenu(0);
  }
}