# Teste HT16K33 Básico

Teste básico do display 7 segmentos HT16K33.

## Placa Alvo
- Arduino UNO

## Componentes Necessários
- Display HT16K33 (7 segmentos)
- Resistor pull-up 10kΩ

## Bibliotecas Utilizadas
- `HT16K33Disp.h` - Biblioteca para display HT16K33

## Funcionalidades
- Exibição de texto "GAME" e "OVER"
- Alternância automática entre textos
- Controle de brilho
- Interface I2C

## Conexões
- HT16K33 VCC: 5V
- HT16K33 GND: GND
- HT16K33 SDA: A4
- HT16K33 SCL: A5

## Como Compilar
1. Abra o arquivo `TesteHT16K33.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale a biblioteca HT16K33Disp
4. Compile e faça upload

## Funcionalidades do Display
- 4 dígitos de 7 segmentos
- Comunicação I2C
- Brilho ajustável
- Suporte a caracteres alfanuméricos

## Aplicações
- Contadores
- Relógios
- Medidores
- Jogos simples
