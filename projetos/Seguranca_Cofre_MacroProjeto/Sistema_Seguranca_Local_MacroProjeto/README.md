# Sistema de Segurança Local

Sistema de segurança standalone sem conectividade de rede.

## Placa Alvo
- ESP32

## Componentes Necessários
- Sensor PIR (movimento)
- Sensor ultrassônico HC-SR04
- Buzzer
- LEDs indicadores
- Teclado matricial (opcional)

## Funcionalidades
- Detecção de movimento (PIR)
- Medição de distância (ultrassônico)
- Sistema de senha local
- Alertas sonoros e visuais
- Operação offline

## Conexões
- PIR: Pino configurado
- Ultrassônico: Trig e Echo configurados
- Buzzer: Pino configurado
- LEDs: Pinos configurados

## Como Compilar
1. Abra o arquivo `SDC.ino` na IDE Arduino
2. Selecione a placa: ESP32 Dev Module
3. Compile e faça upload

## Configuração
- Configure senha via Serial Monitor
- Ajuste sensibilidade dos sensores
- Configure tempo de alerta
- Teste sistema de detecção

## Funcionalidades de Segurança
- Detecção de intrusão
- Medição de proximidade
- Sistema de alarme
- Feedback visual e sonoro
- Operação independente de rede
