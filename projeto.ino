// Bibliotecas para uso do Display de LED
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Biblioteca do Motor
#include <Servo.h>

#define portaServo 8
#define portaBotao 7
#define portaLED 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo meuServo;

void padrao();
void escrever(const char *texto);

void setup() {
  meuServo.attach(portaServo);
  lcd.init();
  lcd.backlight();

  padrao();

  pinMode(portaBotao, INPUT);
  pinMode(portaLED, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(portaBotao);

  if (buttonState == HIGH) {
    for (int i = 10; i > 0; i--) {
      lcd.clear();
      escrever("Tempo Restante:        ");

      if (i < 10) {
        lcd.print("0");
      }

      lcd.print(i);

      digitalWrite(portaLED, HIGH);
      delay(500);
      digitalWrite(portaLED, LOW);
      delay(500);
    }

    lcd.clear();
    escrever("Tirando foto...");

    // Faz aquele efeito de apagar e desligar várias vezes na hora da foto
    for (int i = 0; i < 10; i++) {
      digitalWrite(portaLED, HIGH);
      delay(50);
      digitalWrite(portaLED, LOW);
      delay(50);
    }

    meuServo.write(0);
    delay(1000);
    meuServo.write(180);

    escrever("Obrigado =)");
    delay(2000);

    padrao();
  }

  delay(100);
}

// Volta o display ao texto inicial
void padrao() {
  lcd.clear();

  escrever("Aperte para     tirar uma foto!");

  lcd.setCursor(0, 0);
}

// Escreve no display já contando que ele só tem 16 caracteres por linha
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
