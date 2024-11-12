#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo meuServo;

void padrao();
void escrever(const char *texto);

void setup() {
  meuServo.attach(8);
  lcd.init();
  lcd.backlight();

  padrao();

  pinMode(7, INPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(7);

  if (buttonState == HIGH) {
    for (int i = 3; i > 0; i--) {
      lcd.clear();
      lcd.print("Cronômetro: ");
      lcd.print(i);
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(2, LOW);
      delay(500);
    }

    for (int i = 0; i < 10; i++) {
      digitalWrite(2, HIGH);
      delay(50);
      digitalWrite(2, LOW);
      delay(50);
    }

    meuServo.write(0);
    delay(1000);
    meuServo.write(180);

    padrao();
  }

  delay(100);
}

void padrao() {
  lcd.clear();

  escrever("Aperte para tirar uma foto");

  lcd.setCursor(0, 0);
}

void escrever(const char *texto) {
  int length = strlen(texto);

  for (int i = 0; i < length; i += 32) {
    char line1[17] = "";
    char line2[17] = "";

    strncpy(line1, texto + i, 16);

    if (i + 16 < length) {
      strncpy(line2, texto + i + 16, 16);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}
