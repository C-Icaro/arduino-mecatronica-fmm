#include <LiquidCrystal_I2C.h>
#include <Wire.h>


// DEFINIÇÕES
#define endereco  0x27 // Endereços comuns: 0x27, 0x3F
#define colunas   16
#define linhas    2
#define red 8
#define yellow 12
#define green 13


LiquidCrystal_I2C lcd(endereco, colunas, linhas);

void setup() {
  lcd.init(); // INICIA A COMUNICAÇÃO COM O DISPLAY
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  lcd.clear(); // LIMPA O DISPLAY

  pinMode(red,INPUT_PULLUP);
  pinMode(yellow,INPUT_PULLUP);
  pinMode(green,INPUT_PULLUP);

  lcd.print("Projeto");
  delay(5000);
  lcd.setCursor(0, 1);
  lcd.print("Fluidrium");
  delay(5000);
 
  lcd.noBacklight();
  delay(5000); // DELAY DE 2 SEGUNDOS
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  delay(5000); // DELAY DE 2 SEGUNDOS
 
  lcd.clear(); // LIMPA O DISPLAY
  //lcd.noBacklight(); // DESLIGA A ILUMINAÇÃO DO DISPLAY
}

void loop() {
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Escolha o nivel");
  lcd.setCursor(0, 1); // POSICIONA O CURSOR NA PRIMEIRA COLUNA DA LINHA 2
  lcd.print("1, 2 ou 3");
  delay(1000);
  nivel();
}


void nivel(){
  lcd.clear();
if (!digitalRead(red)){
    lcd.print ("Nivel 3");
    delay (5000);
    }

    else if (!digitalRead(yellow)) {
      lcd.print ("Nivel 2");
      delay(5000);
      }

      else if (!digitalRead(green)){
        lcd.print ("Nivel 1");
        delay(5000);
        }

}
