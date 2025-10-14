# Código Estação - Estação Meteorológica IoT

O projeto da Estação Meteorológica já estava pronto. O cliente Em*** Be**** solicitou que fosse alterado o caminho de envio e retorno dos dados, pois o servidor antigo já não existia mais. O código é um sistema completo para de estação meteorológica baseado em ESP32 com interface web, conectividade WiFi, MQTT e múltiplos sensores ambientais.

## Placa Alvo
- ESP32 Dev Module

## Componentes Necessários
- ESP32 Dev Module
- Sensor BME280 (temperatura, umidade, pressão)
- Sensor ADS1115 (ADC de alta precisão)
- Pluviômetro (sensor de chuva)
- Anemômetro (sensor de vento)
- Sensor DS18B20 (temperatura adicional)
- Sensor EC-5 (umidade do solo)
- LEDs indicadores (vermelho, amarelo, verde)
- Botão de debug
- Módulo WiFi integrado (ESP32)

## Bibliotecas Utilizadas
- `Arduino.h` - Core Arduino
- `SPIFFS.h` - Sistema de arquivos
- `WiFi.h` - Conectividade WiFi
- `Adafruit_BME280.h` - Sensor ambiental
- `Adafruit_ADS1X15.h` - ADC de precisão
- `MQTT.h` - Protocolo MQTT
- `HTTPClient.h` - Cliente HTTP
- `HTTPUpdate.h` - Atualizações OTA
- `WebServer.h` - Servidor web
- `ESP32Time.h` - Gerenciamento de tempo

## Configurações de Hardware

### Estação uKate (Padrão)
```cpp
#define estacao uKate
```

**Pinagem:**
- **VCC_EC5**: Pino 27 (alimentação sensor EC-5)
- **INITIALIZE_PIN_1**: Pino 18 (alimentação sensores)
- **INITIALIZE_PIN_2**: Pino 5 (alimentação sensores)
- **RED_LED**: Pino 17 (LED vermelho)
- **YELLOW_LED**: Pino 16 (LED amarelo)
- **GREEN_LED**: Pino 4 (LED verde)
- **DEBUG_PIN**: Pino 14 (botão debug)
- **PLUVIOMETER_PIN**: Pino 35 (pluviômetro)
- **DS18B20_PIN**: Pino 19 (sensor temperatura)
- **ANEM_PIN**: Pino 19 (anemômetro)
- **BATERIA_PIN**: Pino 36 (monitoramento bateria)

### Estação Kate3
```cpp
#define estacao Kate3
```

### Estação Kate4
```cpp
#define estacao Kate4
```

## Funcionalidades

### Sistema de Sensores
- **Temperatura**: BME280 + DS18B20
- **Umidade**: BME280 + EC-5 (solo)
- **Pressão Atmosférica**: BME280
- **Chuva**: Pluviômetro com contagem de pulsos
- **Vento**: Anemômetro (velocidade média e rajadas)
- **Bateria**: Monitoramento de tensão

### Conectividade
- **WiFi**: Múltiplas redes configuráveis
- **MQTT**: Publicação de dados em tempo real
- **HTTP**: Interface web para configuração
- **OTA**: Atualizações remotas
- **NTP**: Sincronização de tempo

### Interface Web
- **Configuração**: Setup via navegador
- **Monitoramento**: Visualização de dados
- **Rede**: Gerenciamento de conexões WiFi
- **Atualização**: Sistema OTA integrado

## Variáveis de Dados

### Sensores Ambientais
```cpp
float Chuva;           // Precipitação (mm)
float Temperatura;     // Temperatura (°C)
float Umidade;         // Umidade relativa (%)
float Pressao;         // Pressão atmosférica (hPa)
float Vento_Media;     // Velocidade média do vento (m/s)
float Vento_Rajada;    // Velocidade máxima do vento (m/s)
```

### Controle de Pulsos
```cpp
int tPulsos_Chuva = 0;                    // Contador de chuva
int tPulsos_Anemometro_menor_duracao;     // Menor duração de pulso
int tPulsos_Anemometro_quantidade;        // Quantidade de pulsos
```

## Sistema de Flags

### Controle de Estado
```cpp
bool flag_debug = true;                    // Modo debug
bool flag_SENSOR_BME = false;             // Status sensor BME280
bool flag_Envio_MQTT = false;              // Status envio MQTT
bool flag_F_wifi_redes = false;           // Configuração WiFi
bool flag_F_configuracoes = false;        // Configurações gerais
```

### Mensagens de Interface
```cpp
bool Mensagem_Reiniciar = false;          // Reinicialização
bool Mensagem_Atualizar = false;          // Atualização OTA
bool Mensagem_rede_adicionar = false;     // Adicionar rede
bool Mensagem_rede_remover = false;       // Remover rede
bool Mensagem_Espere = false;             // Aguardar operação
```

## Configuração de Rede

### Múltiplas Redes WiFi
```cpp
String ssid[20];                          // SSIDs das redes
String password[20];                      // Senhas das redes
bool flag_internet_connection[20];       // Status das conexões
int rede_atual = 0;                       // Rede ativa
int n_Redes = 0;                          // Número de redes
```

### Servidor Web
```cpp
WebServer server(80);                     // Servidor na porta 80
static const String CONFIG_PAGE = "/html/index.html";
static const String ERROR_PAGE = "/html/fail.html";
static const String SUCCESS_PAGE = "/html/success.html";
```

## Sistema de Tempo

### Sincronização NTP
```cpp
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;             // GMT+0
const int daylightOffset_sec = 3600*3;    // GMT-3 (Brasil)
ESP32Time rtc(-3*3600);                   // RTC interno
```

## Interface HTML

### Páginas Web
- **Index**: Página principal de configuração
- **Success**: Confirmação de operações
- **Fail**: Página de erro
- **Estilo**: CSS integrado com fonte Courier New

### Funcionalidades Web
- Configuração de redes WiFi
- Monitoramento de sensores
- Controle de LEDs
- Atualização OTA
- Reinicialização remota

## Como Compilar

1. **Configure a Estação**: Edite `Hardware_Kate.h` e defina a estação desejada
2. **Abra o Projeto**: Carregue `main.cpp` na IDE Arduino
3. **Selecione a Placa**: ESP32 Dev Module
4. **Instale Bibliotecas**:
   - Adafruit BME280 Library
   - Adafruit ADS1X15 Library
   - MQTT Library
   - ESP32Time Library
5. **Configure WiFi**: Defina credenciais de rede
6. **Compile e Upload**: Faça upload do código

## Configuração Inicial

### Via Interface Web
1. Conecte-se ao WiFi da estação
2. Acesse `http://192.168.4.1`
3. Configure redes WiFi disponíveis
4. Defina parâmetros MQTT
5. Salve configurações

### Via Código
```cpp
// Configurar redes WiFi
ssid[0] = "Nome_da_Rede";
password[0] = "Senha_da_Rede";

// Configurar MQTT
MQTT_Client.begin("broker.mqtt.com", WIFI_Client);
```

## Monitoramento

### LEDs Indicadores
- **Verde**: Sistema funcionando normalmente
- **Amarelo**: Configuração em andamento
- **Vermelho**: Erro ou problema detectado

### Debug Serial
```cpp
void debug(String texto) {
  if(flag_debug) {
    Serial.println(texto);
  }
}
```

## Aplicações

### Meteorologia
- Estações meteorológicas automáticas
- Monitoramento climático local
- Coleta de dados ambientais

### Agricultura
- Monitoramento de solo (EC-5)
- Controle de irrigação
- Análise de condições climáticas

### IoT Industrial
- Monitoramento ambiental industrial
- Sistemas de alerta climático
- Coleta de dados para análise

## Manutenção

### Verificações Regulares
- Limpeza dos sensores
- Verificação de conexões
- Monitoramento de bateria
- Teste de conectividade WiFi

### Troubleshooting
- **Sem conexão**: Verificar configurações WiFi
- **Dados incorretos**: Calibrar sensores
- **LED vermelho**: Verificar logs de debug
- **OTA falha**: Verificar conectividade

## Segurança

### Precauções
- Senhas WiFi seguras
- Broker MQTT autenticado
- Atualizações OTA verificadas
- Backup de configurações

### Limitações
- Dependência de conectividade
- Sensores expostos ao ambiente
- Consumo de bateria
- Alcance WiFi limitado
