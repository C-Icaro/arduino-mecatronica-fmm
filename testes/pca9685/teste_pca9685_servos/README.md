# Teste PCA9685 com Servos

Teste básico do módulo PCA9685 controlando servos motores.

## Placa Alvo
- Arduino UNO

## Componentes Necessários
- Módulo PCA9685 (PWM Servo Driver)
- Servos motores (até 8 unidades)
- Potenciômetro 10kΩ

## Bibliotecas Utilizadas
- `Adafruit_PWMServoDriver.h` - Controle do PCA9685

## Funcionalidades
- Controle de até 8 servos simultaneamente
- Teste de movimento com potenciômetro
- Configuração de frequência PWM (60Hz)
- Monitoramento via Serial

## Conexões
- PCA9685: SDA (A4), SCL (A5), VCC (5V), GND
- Potenciômetro: Pino A1
- Servos: Conectados aos canais 0-7 do PCA9685

## Configurações
- Frequência PWM: 60Hz (padrão para servos analógicos)
- Range de pulso: 125-625 (SERVOMIN-SERVOMAX)
- Endereço I2C: 0x40 (padrão)

## Como Compilar
1. Abra o arquivo `TestePCA9685.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale a biblioteca Adafruit_PWMServoDriver
4. Compile e faça upload

## Teste
- Gire o potenciômetro para controlar os servos
- Monitore os valores no Serial Monitor
- Verifique o movimento suave dos servos
