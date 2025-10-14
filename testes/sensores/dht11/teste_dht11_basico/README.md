# Teste DHT11 Básico

Leitura básica de temperatura e umidade com sensor DHT11.

## Placa Alvo
- Arduino UNO

## Componentes Necessários
- Sensor DHT11
- Resistor pull-up 10kΩ (opcional)

## Bibliotecas Utilizadas
- `dht11.h` - Biblioteca para sensor DHT11

## Funcionalidades
- Leitura de temperatura em Celsius
- Leitura de umidade relativa (%)
- Exibição no Serial Monitor
- Atualização a cada 2 segundos

## Conexões
- DHT11 VCC: 5V
- DHT11 GND: GND
- DHT11 Data: Pino 13
- Resistor pull-up: Entre Data e VCC (opcional)

## Como Compilar
1. Abra o arquivo `TesteDHT11.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale a biblioteca dht11
4. Compile e faça upload

## Monitoramento
- Abra o Serial Monitor (115200 baud)
- Observe as leituras de temperatura e umidade
- Verifique a estabilidade das medições

## Especificações DHT11
- Temperatura: 0-50°C (±2°C)
- Umidade: 20-90% RH (±5% RH)
- Resolução: 1°C / 1% RH
- Tempo de resposta: <5s
