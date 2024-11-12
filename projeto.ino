#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();

  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
}

void loop() {
  lcd.setCursor(0, 1);
  
  for (int i = 10; i >= 0; i--) {
    lcd.print("Countdown: ");
    lcd.print(i);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 1);
 }
}
