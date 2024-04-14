#include <LCD-I2C.h>

LCD_I2C lcd(0x27, 20, 4); //Initialising LCD
//This is for storing the 2 custom symbols that are 2x2
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
  //initing the LCD
  lcd.begin();
  lcd.display();
  lcd.backlight();
  //setting up the custom characters
  for(int i = 0;i<8;i++){
    lcd.createChar(i, CustomPictures[i]);
  }
}

void DisplayBeninging() {
  DisplaySetup();
  //Title
  lcd.setCursor(3, 0);
  lcd.print("Engine testing");
  lcd.setCursor(7, 1);
  lcd.print("station");
  //the top row
  lcd.setCursor(16, 2);
  lcd.write(0);
  lcd.write(1);
  lcd.write(4);
  lcd.write(5);
  //the bottom row
  lcd.setCursor(16, 3);
  lcd.write(2);
  lcd.write(3);
  lcd.write(6);
  lcd.write(7);
  //end of the start up screen
  delay(2000);
  lcd.clear();
}
