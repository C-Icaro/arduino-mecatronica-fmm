#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Criação dos objetos para as 3 placas PCA9685 com endereços diferentes
Adafruit_PWMServoDriver placa1 = Adafruit_PWMServoDriver(0x41); // Endereço padrão
Adafruit_PWMServoDriver placa2 = Adafruit_PWMServoDriver(0x42); // Endereço A0 alterado
Adafruit_PWMServoDriver placa3 = Adafruit_PWMServoDriver(0x43); // Endereço A1 alterado

const int potPin = A0; // Pino do potenciômetro
int valorPot;          // Variável para armazenar leitura do potenciômetro

void setup() {
  Serial.begin(9600);
  
  // Inicializa as 3 placas com a frequência de 50 Hz
  placa1.begin();
  placa1.setPWMFreq(50);

  placa2.begin();
  placa2.setPWMFreq(50);

  placa3.begin();
  placa3.setPWMFreq(50);

  Serial.println("Inicialização concluída!");
}

void loop() {
  // Lê o valor do potenciômetro (0 a 1023)
  valorPot = analogRead(potPin);

  // Converte para o intervalo de pulsos PWM (1 ms a 2 ms → 205 a 410)
  int valorPWM = map(valorPot, 0, 1023, 205, 410);

  // Envia o valor PWM para um canal em cada placa
  for(int i=0; i<16; i++){
  placa1.setPWM(i, 0, valorPWM); // Canal 0 da placa 1
  placa2.setPWM(i, 0, valorPWM); // Canal 1 da placa 2
  placa3.setPWM(i, 0, valorPWM); // Canal 2 da placa 3
  }

  // Exibe os valores no monitor serial
  Serial.print("Potenciômetro: "); Serial.print(valorPot);
  Serial.print(" | PWM: "); Serial.println(valorPWM);

  delay(50); // Pequeno atraso para estabilidade
}
