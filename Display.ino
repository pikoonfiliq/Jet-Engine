#include <LCD-I2C.h>

LCD_I2C lcd(0x27, 20, 4);

void DisplaySetup(){
  //inniting the LCD
  lcd.begin();
  lcd.display();
  lcd.backlight();

}

void DisplayBeninging(){
  DisplaySetup();
  lcd.setCursor(3, 0);
  lcd.print("Engine testing");
  lcd.setCursor(7, 1);
  lcd.print("station");
  delay(5000);
  lcd.clear();
}


