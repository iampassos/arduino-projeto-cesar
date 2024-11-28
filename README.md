# Projeto Viva o_Antigo
O projeto Viva o antigo consiste em uma câmera de impressão térmica juntamente com arduino que permite aos usuários registrarem momentos com ela.
A solução técnica que foi usada para esse projeto é composta de diferentes modais dentro de um modelo de câmera fotográfica que remete às primeiras criadas na história. 

O projeto é composto de três partes: 1 - Estrutura, 2 - Arduino, 3 - Câmera e impressora.

## 🧱 Estrutura
O Projeto tem como estrutura uma caixa feita em MDF em formato análogo as câmeras fotográficas antigas e uma tela e botão, conectados ao arduino.

## 🤖 Arduino
responsável pelo código do projeto, através dele foi criado um sistema que utiliza um display LCD, um botão e um servo motor.
Quando o botão é pressionado, inicia uma contagem regressiva de 10 segundos, e após o tempo, o sistema simula o processo de tirar uma foto, movendo o servo e piscando um LED.
O display LCD exibe mensagens em todas as etapas do processo

## 📷Câmera e 🖨️impressora
responsável por registrar a foto para o usuário e imprimi-la.

How to Use do Projeto Viva o Antigo:  
1 - Pressione o botão.localizado no lado da caixa.  
2 - o LCD irá notificar o tempo restante para a foto, com esse tempo,se organize para o registro da foto.  
3 - após a contagem do cronômetro terminar, o LCD irá notificar que a foto está sendo registrada com a mensagem "Tirando foto...", além disso, o LED vai disparar simulando o "disparo da foto".  
4 - O LCD exibe a mensagem "Obrigado =)" e retorna para o estado inicial no intuito de realizar-lo outra vez.


Explicação do código:  
#include <LiquidCrystal_I2C.h>  
#include <Servo.h>  
#include <Wire.h>
1 - Nessa parte do código são incluídas bibliotecas no código. A seguir serão explicadas cada uma dessas funções individualmente:
1º - include <LiquidCrystal_I2C.h> : Esta biblioteca permite controlar um display LCD com interface I2C, simplificando o uso de displays LCD com dois fios (SDA e SCL).  
2º - include <Servo.h> : Biblioteca que possui as funções necessárias para posicionar o servo para a posição desejada.
3º - #include <Wire.h> : Biblioteca que permite comunicação com dispositivos I2C/TWI.  
LiquidCrystal_I2C lcd(0x27, 16, 2);  
Servo meuServo;  
2 - Nessa parte do código são declarados:  
1º - lcd(0x27, 16, 2) : cria um objeto lcd para controlar o display LCD com I2C.O 1º número é o endereço do dispositivo,que é 0x27, nomenclatura comum para LCD com I2C.os outros dois são as quantidades de 
 colunas e linhas que o display possui,sendo tais quantitades: 16 colunas e 2 linhas.  
2º - meuServo : Cria um objeto meuServo para controlar um servo motor.  
void padrao();  
void escrever(const char *texto);  
3 - Nessa parte do código são declaradas funções utilizadas posteriormente no código:  
1º - padrao() : Função para exibir uma mensagem padrão no display LCD.  
2º - escrever(const char *texto) : Função para exibir uma mensagem no display LCD.
  
void setup() {  
meuServo.attach(8);  
lcd.init();  
lcd.backlight();
  
  padrao();
  
  pinMode(7, INPUT);  
  pinMode(2, OUTPUT);  
}  
4 - Nessa parte do código foi feita uma função setup, na qual cada parte do código faz:  
1º - meuServo.attach(8) : Conecta o servo motor ao pino 8 do Arduino.  
2º - lcd.init(): Inicializa o display LCD.  
3º - lcd.backlight(): Ativa a luz de fundo do LCD.  
4º - padrao() : Chama a função padrao() para exibir uma mensagem inicial.  
5:º - pinMode(7, INPUT): Configura o pino 7 como uma entrada (para o botão).  
6º - pinMode(2, OUTPUT): Configura o pino 2 como uma saída (para o controle de um LED ou outro dispositivo).
  
void loop() {  
int buttonState = digitalRead(7);
  
if (buttonState == HIGH) {  
  for (int i = 10; i > 0; i--) {  
  lcd.clear();  
  escrever("Tempo Restante:        ");  
  if (i < 10) {  
  lcd.print("0");  
  lcd.print(i);  
  } else {  
  lcd.print(i);  
  }  
  digitalWrite(2, HIGH);  
  delay(500);  
  digitalWrite(2, LOW);  
  delay(500);  
  }
  
  lcd.clear();  
  escrever("Tirando foto...");
  
  for (int i = 0; i < 10; i++) {  
  digitalWrite(2, HIGH);  
  delay(50);  
  digitalWrite(2, LOW);  
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
5 - Nessa parte do código é feito uma função loop na qual o código em suas diferentes partes faz:  
1º - buttonState = digitalRead(7) : Lê o estado do botão no pino 7. Se o botão for pressionado, buttonState será HIGH.  
2º - if (buttonState == HIGH): Se o botão estiver pressionado, o código dentro do if é executado.  
3º - for (int i = 10; i > 0; i--): Um contador de 10 segundos que conta de 10 até 0, onde a cada segundo o display é atualizado com a contagem.  
4º - lcd.clear() : Limpa o display do LCD.  
5º - escrever("Tempo Restante: "): Exibe a mensagem "Tempo Restante: " com o número de segundos restantes sendo exibido com formatação, com dois dígitos.  
6º - digitalWrite(2, HIGH/LOW): Acende e apaga o LED conectado ao pino 2, tentando criar um efeito similar ao do flash de câmeras fotográficas.  
7º - delay(500): Atraso de 500 milissegundos.  
8º - meuServo.write(0): Move o servo para o ângulo 0 (posição inicial).  
9º - delay(1000) : Aguarda 1 segundo.  
10º - meuServo.write(180): Move o servo para o ângulo 180 no intuito de pressionar o botão da câmera para o registro da foto.  
11º - escrever("Obrigado =)") : Exibe uma mensagem de agradecimento no LCD.  
12º - delay(2000) : Aguarda 2 segundos antes de reiniciar o processo.  
13º - padrao() : Chama a função padrao() para exibir a mensagem inicial.  
14º - delay(100) : Aguarda 100 milissegundos antes de verificar o estado do botão novamente.
  
void padrao() {  
lcd.clear();
  
  escrever("Aperte para     tirar uma foto!");
  
  lcd.setCursor(0, 0);  
  }  
6 - Nessa parte do código é definida a função padrao onde:  
1º - lcd.clear() : Limpa o display.  
2º - escrever("Aperte para tirar uma foto!") : Exibe a mensagem "Aperte para tirar uma foto!" no LCD.  
3º - lcd.setCursor(0, 0): Define o cursor no início da linha 0.
  
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
7 - Nessa parte do código foi definida a função escrever(const char *texto) na qual cada parte do código faz:  
1º - strlen(texto) : Calcula o comprimento da string passada como argumento.  
2º - for (int i = 0; i < length; i += 32) : Um loop para dividir o texto em partes de até 32 caracteres.  
3º - strncpy(line1, texto + i, 16) : Copia até 16 caracteres da string de texto para a linha 1 do display LCD.  
4º - strncpy(line2, texto + i + 16, 16) : Copia os próximos 16 caracteres (se tiver) para a linha 2 do display LCD.  
5º - lcd.clear() : Limpa o display antes de mostrar as novas linhas de texto.  
6º - lcd.setCursor(0, 0) e lcd.setCursor(0, 1) : Define as posições do cursor para a linha 1 e 2, respectivamente.  
7º - lcd.print(line1) e lcd.print(line2) : Exibe as linhas de texto no display.
