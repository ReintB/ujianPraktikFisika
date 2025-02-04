#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows

void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();

  lcd.setCursor(0, 0);            // move cursor the first row
  lcd.print("Reinhart Barus");          // print message at the first row
  lcd.setCursor(0, 1);            // move cursor to the second row
  lcd.print("Thomas Barus"); // print message at the second row
  lcd.setCursor(0, 2);            // move cursor to the third row
  lcd.print("Sukmanita Br Bangun");          // print message at the third row
  lcd.setCursor(0, 3);            // move cursor to the fourth row
  lcd.print("MANTAP PANCING");   // print message the fourth row
}

void loop() {
}