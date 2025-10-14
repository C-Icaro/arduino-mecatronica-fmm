# Sistema de Segurança Multinível

Sistema de segurança com múltiplos sensores e integração Firebase.

## Placa Alvo
- ESP32

## Componentes Necessários
- Sensor PIR (movimento)
- Sensor ultrassônico HC-SR04
- Sensor IR (infravermelho)
- Buzzer
- LEDs indicadores
- Módulo WiFi integrado (ESP32)

## Bibliotecas Utilizadas
- `WiFi.h` - Conexão WiFi
- `IOXhop_FirebaseESP32.h` - Integração Firebase
- `ArduinoJson.h` - Manipulação JSON

## Funcionalidades
- Detecção por múltiplos sensores (PIR, ultrassom, IR)
- Sistema de senha via Serial
- Sincronização com Firebase
- Alertas sonoros e visuais
- Monitoramento remoto

## Conexões
- PIR: Pino configurado
- Ultrassônico: Trig e Echo configurados
- IR: Pino configurado
- Buzzer: Pino configurado
- LEDs: Pinos configurados

## Como Compilar
1. Abra o arquivo `ProjetoSandiegoDani.ino` na IDE Arduino
2. Selecione a placa: ESP32 Dev Module
3. Configure credenciais WiFi e Firebase
4. Instale as bibliotecas necessárias
5. Compile e faça upload

## Configuração de Segurança
- Configure senhas via Serial Monitor
- Ajuste sensibilidade dos sensores
- Configure alertas Firebase
- Teste cada nível de detecção

## Níveis de Segurança
1. **Nível 1**: Detecção IR
2. **Nível 2**: Detecção ultrassônica
3. **Nível 3**: Detecção PIR
4. **Ativação**: Combinação de sensores + senha
