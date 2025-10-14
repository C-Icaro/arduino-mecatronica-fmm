#include <Wire.h>                        // Biblioteca para comunicação I2C
#include <Adafruit_PWMServoDriver.h>     // Biblioteca para PCA9685

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();  // Objeto PCA9685

const int potPin = A2;            // Pino do potenciômetro

void setup() {
  Serial.begin(9600);
  pwm.begin();                   // Inicializa a comunicação com o PCA9685
  pwm.setPWMFreq(50);            // Frequência de 50 Hz (padrão para ESCs)
  Serial.println("Controle Brushless com PCA9685!");
}

void loop() {
  // Lê o valor do potenciômetro (0 a 1023)
  int valorPot = analogRead(potPin);

  // Mapear para valores de pulso para ESC (servo motor: 1000-2000us -> 0-4095)
  int valorPWM = map(valorPot, 0, 1023, 205, 410);  // Ajustar conforme o motor
  
  // Envia o valor mapeado para o canal específico
  for(int i=0; i<16; i++){
  pwm.setPWM(i, 0, valorPWM);}

  //Exibe os valores no monitor serial
  Serial.print("Valor do Potenciômetro: "); 
  Serial.print(valorPot);
  Serial.print(" | Valor PWM: "); 
  Serial.println(valorPWM);
  delay(20); // Pequeno atraso para estabilidade
}
