# Teste KY-038 - Detecção de Palmas

Detecção simples de palmas usando microfone KY-038.

## Placa Alvo
- ESP32

## Componentes Necessários
- Microfone KY-038
- LEDs para feedback visual

## Funcionalidades
- Detecção de palmas por limiar analógico
- Feedback visual com LEDs
- Monitoramento via Serial
- Ajuste de sensibilidade

## Conexões
- KY-038 VCC: 3.3V
- KY-038 GND: GND
- KY-038 A0: Pino analógico configurado
- LEDs: Conforme definido no código

## Como Compilar
1. Abra o arquivo `Teste_KY038.ino` na IDE Arduino
2. Selecione a placa: ESP32 Dev Module
3. Compile e faça upload

## Configuração
- Ajuste o limiar de detecção conforme ambiente
- Teste diferentes valores para otimizar sensibilidade
- Monitore valores no Serial para calibração

## Aplicações
- Controle por palmas
- Detecção de ruído ambiente
- Sistema de alerta sonoro
- Interface hands-free
