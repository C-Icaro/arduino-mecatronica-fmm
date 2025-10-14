//código para o acionamento de motor brushless sem PCA9685
#include <Servo.h> //inclui a biblioteca Servo
Servo ESC; //cria o objeto ESC
int pot = A2; //informa ao arduino onde o potenciômetro está conectado
void setup(){
  Serial.begin(9600);
  ESC.attach(6); //informa que o ESC está conectado ao pino digital 6
}
void loop(){
 int vel = analogRead(pot); //faz a leitura do potenciômetro
 int PWM = map(vel, 0, 1023, 0, 179); //associa o valor lido à velocidade do motor 
 ESC.write(PWM); //envia os valores recebidos ao ESC

   //Exibe os valores no monitor serial
  Serial.print("Valor do Potenciômetro: "); 
  Serial.print(vel);
  Serial.print(" | Valor PWM: "); 
  Serial.println(PWM);
}