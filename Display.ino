#include <LCD-I2C.h>

LCD_I2C lcd(0x27, 20, 4);
byte CustomPictures[][8] = {
  //fire symbol
  { B00000, B00010, B00011, B00011, B00111, B00111, B00111, B01111 },
  { B00000, B00000, B00000, B00000, B10000, B10100, B10100, B11100 },
  { B01111, B11111, B11110, B11110, B11010, B11000, B11100, B01110 },
  { B11111, B11111, B11111, B11111, B10111, B10111, B10111, B00110 },
  //Warning symbol
  { B00011, B00011, B00011, B00110, B00110, B00110, B00110, B01101 },
  { B11000, B11000, B11000, B01100, B01100, B01100, B01100, B10110 },
  { B01101, B01101, B01101, B11000, B11001, B11001, B11000, B01111 },
  { B10110, B10110, B10110, B00011, B10011, B10011, B00011, B11110 }
};

void DisplaySetup() {
  //inniting the LCD
  lcd.begin();
  lcd.display();
  lcd.backlight();
  for (int i = 0; i < 8; i++) {
    lcd.createChar(i, CustomPictures[i]);
  }
}

void DisplayBeninging() {
  DisplaySetup();
  lcd.setCursor(3, 0);
  lcd.print("Engine testing");
  lcd.setCursor(7, 1);
  lcd.print("station");

  lcd.setCursor(16, 2);
  lcd.write(0);
  lcd.write(1);
  lcd.write(4);
  lcd.write(5);

  lcd.setCursor(16, 3);
  lcd.write(2);
  lcd.write(3);
  lcd.write(6);
  lcd.write(7);

  delay(2500);
  lcd.clear();
}

void DisplayChooseMenu(int selectFlag) {
  lcd.setCursor(0, 0);
  lcd.print("Choose setting:");
  lcd.setCursor(0, 1);
  if (Mode == 0) {
    lcd.print(">");
  } else {
    lcd.print(" ");
  }
  lcd.print("Manual");
  lcd.setCursor(0, 2);
  if (Mode == 1) {
    lcd.print(">");
  } else {
    lcd.print(" ");
  }
  lcd.print("Autopilot");
  if (selectFlag == 1) {
    lcd.setCursor(0, 3);
    lcd.print("Mode selected");
    delay(1000);
    lcd.clear();
  }
  delay(100);
}

void DisplayMainMenu() {
  lcd.setCursor(0, 0);
  lcd.print("Mode: ");
  switch (Mode) {
    case 0:
      lcd.print("Manual");
      break;

    case 1:
      lcd.print("Autopilot");
      break;

    default:
      lcd.print("Error");
      break;
  }
  lcd.setCursor(0, 1);
  lcd.print("Status: ");
  switch (Stage) {
    case 0:
      lcd.print("Off        ");
      break;
    case 1:
      lcd.print("Starting up");
      break;
    case 2:
      lcd.print("On         ");
      break;
    case 3:
      lcd.print("Cooling off");
      break;
    default:
      lcd.print("Error      ");
      break;
  }

  switch (Mode) {
    case 0:
      DisplayManual();
      break;
    case 1:
      DisplayAuto();
      break;
    default:
      lcd.print("Controls Error");
      break;
  }
  String FieldVal1 = "Tem:" + String(Temperature) + char(0xDF) +"C";
  for (int i = FieldVal1.length(); i < 10; i++) {
    FieldVal1 += " ";
  }
  String FieldVal2 = "Thr:" + String(Thrust) + "kg";
  for (int i = FieldVal2.length(); i < 10; i++) {
    FieldVal2 += " ";
  }
  lcd.setCursor(0, 3);
  lcd.print(FieldVal1);
  lcd.setCursor(9, 3);
  lcd.print(FieldVal2);
}

void DisplayManual() {
  String FieldVal1 = "Gas:" + String(GasVal) + "%";
  for (int i = FieldVal1.length(); i < 10; i++) {
    FieldVal1 += " ";
  }
  String FieldVal2 = "Air:" + String(AirVal) + "%";
  for (int i = FieldVal2.length(); i < 10; i++) {
    FieldVal2 += " ";
  }
  lcd.setCursor(0, 2);
  lcd.print(FieldVal1);
  lcd.setCursor(9, 2);
  lcd.print(FieldVal2);
}
void DisplayAuto() {
  String FieldVal = "Speed:" + String(SpeedVal) + "%";
  for (int i = FieldVal.length(); i < 20; i++) {
    FieldVal += " ";
  }
  lcd.setCursor(0, 2);
  lcd.print(FieldVal);
}
