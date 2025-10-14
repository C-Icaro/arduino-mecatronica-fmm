# Smart Home by Voice

O projeto Smart Home by Voice foi desenvolvido para obtenção parcial da nota da matéria de Desenvolvimento de Sistemas Integrados (DSI). Ele tem como função a integração de ao menos 3 sistemas diferentes por IOT. Nesse caso, foi feito um estudo aprofundado sobre o uso do sensor KY-038 como microfone barato para captação de voz para acionamento de fitas de led. No entanto, foi percebido que o mesmo tinha limitações e não conseguia distinguir entre diferentes sons, apenas as suas intensidades.

Por conta disso, o projeto foi limitado a intensidade da voz e acionamento de duas fitas de led. Um comando baixo muda o estado da fita 1 e um comando alto muda o estado da fita 2.


## Placa Alvo
- ESP32 (ESP32DOIT-DEVKIT-V1)

## Componentes Necessários
- Microfone KY-038
- 2 fitas de LED
- Mesa/atuador de controle
- Módulo WiFi integrado (ESP32)

## Bibliotecas Utilizadas
- `WiFi.h` - Conexão WiFi
- `IOXhop_FirebaseESP32.h` - Integração Firebase
- `dht11.h` - Sensor DHT11

## Funcionalidades
- Detecção de áudio via microfone
- Controle de fitas LED e mesa
- Sincronização de dados com Firebase

## Conexões
- DHT11: Pino 12
- Microfone KY-038: Pino 25
- Fita LED 1: Pino 26
- Fita LED 2: Pino 27
- Mesa/Atuador: Pino 14

## Como Compilar
1. Abra o arquivo `.ino` na IDE Arduino
2. Selecione a placa: ESP32 Dev Module
3. Configure as credenciais WiFi e Firebase
4. Instale as bibliotecas necessárias
5. Compile e faça upload

## Funcionalidades IoT
- Envio automático de dados de sensores
- Controle remoto via Firebase
- Monitoramento em tempo real
- Sistema baseado em áudio
