#include <Arduino.h>
#include "Hardware_Kate.h"
#include "SPIFFS.h"
#include "esp_WiFi.h"
#include "WiFi.h"
#include <Adafruit_BME280.h>
#include <Adafruit_ADS1X15.h>
#include <MQTT.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <htmls.h>
#include <WebServer.h>
#include "time.h"
#include <ESP32Time.h>
//#include <wdt.h>

const float inf = INFINITY;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0; // Pega a hora no fuso horario 0, o de brasilia é GMT-3, no rtc interno é ajustado para ficar no GMT-3
const int   daylightOffset_sec = 3600*3;
ESP32Time rtc(-3*3600);  // offset em segundos GMT+3

bool Mensagem_Reiniciar = false;
bool Mensagem_Atualizar = false;
bool Mensagem_rede_adicionar = false;
bool Mensagem_rede_remover = false;
bool Mensagem_rede_enviar = false;
bool Mensagem_rede_scan_enviar = false;
bool Mensagem_rede_scan_adicionar = false;
bool Mensagem_Espere = false;
int tempoInterface = 0;
String Payload_Interface = "";

String Versao_Para_Atualizar;
int n_Redes_Disponiveis = 0;

bool flag_MQTT_Reiniciar = false;
bool flag_MQTT_Atualizar = false;
bool flag_MQTT_Redes = false;

bool flag_debug = true;
bool flag_F_wifi_redes = false;
bool flag_F_configuracoes = false;

bool flag_SENSOR_BME = false;

bool flag_Envio_MQTT = false;


int Numero_Dados_salvos = 0;


String ID_Estacao;
String ssid[20];
String password[20];
// criar um vetor booleano flag_internet_connection que inicia com todos os valores true
bool flag_internet_connection[20] = {true};
int rede_atual = 0;

int n_Redes = 0;
MQTTClient MQTT_Client;
WiFiClient WIFI_Client;


WebServer server(80);
static const char* CONTENT_TYPE_HTML = "text/html";
static const char* CONTENT_TYPE_JSON = "text/json";
static const String CONFIG_PAGE = "/html/index.html";
static const String ERROR_PAGE = "/html/fail.html";
static const String SUCCESS_PAGE = "/html/success.html";



Adafruit_BME280 SENSOR_BME;
Adafruit_ADS1115 SENSOR_ADS;



// Variáveis para armazenar os dados dos sensores
int tPulsos_Chuva = 0;
int tPulsos_Anemometro_menor_duracao = 1000000;
int tPulsos_Anemometro_quantidade = 0;

float Chuva;
float Temperatura;
float Umidade;
float Pressao;
float Vento_Media;
float Vento_Rajada;

int Tempo_Ultimo_Envio = 0;



void debug(String texto){
  if(flag_debug){
    Serial.println(texto);
  }
}


// Hardware

void Inicializa_Placa(){  // OK
  
  //wdt_enable(300000);

  if (flag_debug){
    Serial.begin(115200);
  }


  debug("Inicializando Estacao Kate");

  pinMode(DEBUG_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(INITIALIZE_PIN_1, OUTPUT);
  pinMode(INITIALIZE_PIN_2, OUTPUT);
  pinMode(VCC_EC5, OUTPUT);
  pinMode(PLUVIOMETER_PIN, INPUT);
  pinMode(ANEM_PIN, INPUT);

  digitalWrite(INITIALIZE_PIN_1, HIGH);
  digitalWrite(INITIALIZE_PIN_2, HIGH);
  digitalWrite(YELLOW_LED, HIGH);  

}

void Pisca_Leds(){        // OK
  if (WiFi.status() == WL_CONNECTED){
    digitalWrite(GREEN_LED, HIGH);
    delay(250);
    digitalWrite(GREEN_LED, LOW);
    delay(250);
  }
  else{
    digitalWrite(RED_LED, HIGH);
    delay(1000);
    digitalWrite(RED_LED, LOW);
    return;
  }

  if (MQTT_Client.connected()){
    digitalWrite(GREEN_LED, HIGH);
    delay(250);
    digitalWrite(GREEN_LED, LOW);
    delay(250);
  }
  else{
    digitalWrite(RED_LED, HIGH);
    delay(1000);
    digitalWrite(RED_LED, LOW);
    return;
  }

  if (flag_Envio_MQTT){
    digitalWrite(GREEN_LED, HIGH);
    delay(250);
    digitalWrite(GREEN_LED, LOW);
    delay(250);
  }
  else{
    digitalWrite(RED_LED, HIGH);
    delay(1000);
    digitalWrite(RED_LED, LOW);
    return;
  }

  flag_Envio_MQTT = false;

}





// Leitura e Escrita da SPIFFS

void Escrita_F_wifi_Redes(){      // OK
  File wifi_redes = SPIFFS.open("/wifi_redes.txt", "w");
  if (!wifi_redes) {
    debug("Erro ao abrir arquivo de configuração");
    return;
  }
  for(int i=0 ; i<n_Redes ; i++){
    wifi_redes.println(ssid[i]);
    wifi_redes.println(password[i]);
  }
  wifi_redes.close();
}

void Escrita_F_Configuracoes(){   // OK
  File configuracoes = SPIFFS.open("/configuracoes.txt", "w");
  if (!configuracoes) {
    debug("Erro ao abrir arquivo de configuração");
    return;
  }
  if (ID_Estacao == ""){
    ID_Estacao = WiFi.macAddress();
    // remove os dois pontos
    ID_Estacao.replace(":", "");
  }
  configuracoes.println(ID_Estacao);
  configuracoes.close();
}

void Leitura_F_wifi_Redes(){      // OK

  if (SPIFFS.exists("/wifi_redes.txt")) {
    flag_F_wifi_redes = true;
    debug("Arquivo de redes existe");
  } else {
    flag_F_wifi_redes = false;
    debug("Arquivo de redes não existe");
    return;
  }

  File wifi_redes = SPIFFS.open("/wifi_redes.txt", "r");

  debug("Lendo redes salvas");
  n_Redes = 0;
  while(wifi_redes.available()){
    ssid[n_Redes] = wifi_redes.readStringUntil('\n');
    password[n_Redes] = wifi_redes.readStringUntil('\n');
    ssid[n_Redes].trim();
    password[n_Redes].trim();
    debug("SSID: " + ssid[0] + "\tPassword: " + password[0]);


    

    n_Redes++;
  }
  //ssid[0] = "Beal";
  //password[0] = "244466666";
  debug("Arquivo de redes lido com sucesso");

}

void Leitura_F_Configuracoes(){   // OK
  File configuracoes = SPIFFS.open("/configuracoes.txt", "r");
  if (!configuracoes) {
    flag_F_configuracoes = false;
    Escrita_F_Configuracoes();
    return;
  } else {
    flag_F_configuracoes = true;
  }

  while(configuracoes.available()){
    ID_Estacao = configuracoes.readStringUntil('\n');
  }
  ID_Estacao.trim();
  debug("ID: " + ID_Estacao);
}

void Escrita_Relatorio_Info(){
  File Relatorio_Info = SPIFFS.open("/Relatorio_Info.txt", "w");
  if (!Relatorio_Info) {
    debug("Erro ao abrir o arquivo de informacoes do relatorio");
    return;
  }

  Relatorio_Info.println(Numero_Dados_salvos);
  Relatorio_Info.close();
}

void Leitura_Relatorio_Info(){
  File Relatorio_Info = SPIFFS.open("/Relatorio_Info.txt", "r");
  if (!Relatorio_Info) {
    debug("Erro ao abrir o arquivo de informacoes do relatorio");
    return;
  }

  while(Relatorio_Info.available()){
    Numero_Dados_salvos = Relatorio_Info.readStringUntil('\n').toInt();
  }

  debug("Dados nao Enviados: " + String(Numero_Dados_salvos));
}

void Escrita_Relatorio(){
  File Relatorio = SPIFFS.open("/Relatorio.txt", "a");
  if (!Relatorio) {
    debug("Erro ao abrir o relatorio");
    return;
  }

  // Salva no arquivo Relatorio a data e a hora atual junto com os dados dos sensores e se foi enviado ou não do jeito mais compacto possivel
  Relatorio.print(rtc.getTime("%B%m%Y%H%M%S"));
  if (flag_SENSOR_BME){
    Relatorio.print("," + String(Temperatura) + "," + String(Umidade) + "," + String(Pressao));
  }
  else{
    Relatorio.print(",,,");
  }
  Relatorio.print("," + String(Chuva));
  Relatorio.print("," + String(Vento_Media));
  Relatorio.print("," + String(Vento_Rajada));
  Relatorio.println(ID_Estacao);
  Relatorio.close();

  Leitura_Relatorio_Info();
  Numero_Dados_salvos++;
  Escrita_Relatorio_Info();


}

void Leitura_Relatorio(){
  File Relatorio = SPIFFS.open("/Relatorio.txt", "r");
  if (!Relatorio) {
    debug("Erro ao abrir o relatorio");
    return;
  }

  while(Relatorio.available()){

    // separa o tempo e os dados de temperatura, umidade, pressao, chuva e vento
    String Tempo = Relatorio.readStringUntil(',');

    String aux = "";
    aux = Relatorio.readStringUntil(',');
    Temperatura = (aux.toInt() || aux.toFloat()) ? aux.toFloat() : -99;

    aux = Relatorio.readStringUntil(',');
    Umidade = (aux.toInt() || aux.toFloat()) ? aux.toFloat() : -99;

    aux = Relatorio.readStringUntil(',');
    Pressao = (aux.toInt() || aux.toFloat()) ? aux.toFloat() : -99;

    Chuva = Relatorio.readStringUntil(',').toFloat();
    Vento_Media = Relatorio.readStringUntil(',').toFloat();
    Vento_Rajada = Relatorio.readStringUntil(',').toFloat();




  }
}

bool Leitura_Conf_Legado(){ // leitura do arquivo de configuracoes do Codigo da Weather-Station
  
    if (!SPIFFS.exists("/config.txt")){
    debug("Arquivo nao encontrado");
    return false;
  }


  File configuracoes = SPIFFS.open("/config.txt", "r");


  while(configuracoes.available()){
    configuracoes.readStringUntil('=');
    ssid[0] = configuracoes.readStringUntil('\n');
    configuracoes.readStringUntil('=');
    password[0] = configuracoes.readStringUntil('\n');
    configuracoes.readStringUntil('=');
    ID_Estacao = configuracoes.readStringUntil('\n');

    debug(ssid[0] + ".");
    debug(password[0] + ".");
    debug(ID_Estacao + ".");
    n_Redes = 1;


  }
  ID_Estacao.trim();
  debug("ID: " + ID_Estacao);

  
  Escrita_F_wifi_Redes();
  Escrita_F_Configuracoes();
  
  
  // fecha o arquivo "/config.txt" e exclui ele
  configuracoes.close();
  //SPIFFS.remove("/config.txt");
  return true;


}
// Configuracao Local

String getHtmlContent(String Arquivo){

    if (Arquivo == CONFIG_PAGE)  return Index;
    if (Arquivo == ERROR_PAGE)   return fail;
    if (Arquivo == SUCCESS_PAGE) return success;
    auto file = SPIFFS.open(Arquivo);
    if (!file) {
		debug("Falha ao abrir o arquivo");
	}
	const String html = file.readString();
	file.close();
	return html;
}

void sendHtmlPage(String Arquivo) {
    server.send (
		HTTP_CODE_OK,
		CONTENT_TYPE_HTML,
        getHtmlContent(Arquivo)
	);
}

void handleRoot() {
	debug("Rodando a request");
	sendHtmlPage(CONFIG_PAGE);
}

void handleConfig() {
	debug("Rodando a request");
  ssid[0] = server.arg(String("ssid"));
  password[0] = server.arg(String("pass"));
  ID_Estacao = server.arg("ID");

  debug("Entrando na rede " + ssid[0]);
  debug("Senha: " + password[0]);




  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid[0].c_str(), password[0].c_str());
  debug("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    debug(String(int(WiFi.status())));
    delay(1000);
  }
  debug(String(int(WiFi.status())));



	if (WiFi.status() != WL_CONNECTED) {
		debug("Falha ao conectar ao wifi\n");
		sendHtmlPage(ERROR_PAGE);
    return;
	}
  sendHtmlPage(SUCCESS_PAGE);
  n_Redes = 1;
  Escrita_F_wifi_Redes();
  Escrita_F_Configuracoes();

	delay(500);
	ESP.restart();
}

void handleRedes() {
	debug("Rodando a request");
	String json = "{\"redes\":[";
	int16_t available_networks = WiFi.scanComplete();
	while (available_networks < 0) {
		if (available_networks == WIFI_SCAN_FAILED) {
			json += "]}";
			server.send(HTTP_CODE_OK, CONTENT_TYPE_JSON, json);
			return ;
		}
		available_networks = WiFi.scanComplete();
	}
	for(int16_t i = 0; i < available_networks; i++) {
		String temp = "\"";
		temp += WiFi.SSID(i);
		temp += "\",";

		json += temp;
	}
	*(json.end() - 1) = ']';
	json += '}';
	server.send(HTTP_CODE_OK, CONTENT_TYPE_JSON, json);
}

void Configuracao_Local(){

  debug("configuracao via WiFi");

  int16_t available_networks =  WiFi.scanNetworks(false,true);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("Conf Estação Kate");

  IPAddress myIP = WiFi.softAPIP();
  debug("AP IP address: ");
  Serial.println(myIP);


  debug("Access point configurado conecte-se a rede: " + String("Conf Estação Kate"));

  String RedesDisponiveis[available_networks];
  int j=0;
  for (int i=0;i<available_networks;i++){
      if (!(WiFi.SSID(i) == "")){
          RedesDisponiveis[j] = WiFi.SSID(i);
          j++;
      }
  }

  

  server.on("/",       HTTP_GET,  handleRoot);
  server.on("/config", HTTP_POST, handleConfig);
  server.on("/redes",  HTTP_GET,  handleRedes);

  server.begin();
  
  debug("Web Server inicializado\n");

  const auto time_limit = millis() + 600000; // 10 minutos
  while (millis() < time_limit) {
      server.handleClient();
      delay(2);
  }

  delay(1000);

  ESP.restart();

}

void Leitura_SPIFFS(){            // OK
  debug("Montando a SPIFFS");
  if (!SPIFFS.begin(true)) {
    debug("Erro ao montar SPIFFS");
  } else {
    debug("SPIFFS montado com sucesso");
  }

  Leitura_F_wifi_Redes();
  if (!flag_F_wifi_redes){
    if (!Leitura_Conf_Legado()){
      Configuracao_Local();
    }
    return;
  }
  Leitura_F_Configuracoes();  
}





// Tasks

void task_SENSOR_PLUVIOMETRO(void * pvParameters){  // OK
  while (true) {
		if (digitalRead(PLUVIOMETER_PIN)) {
			tPulsos_Chuva++;
			debug("Incrementei chuva =" + String(tPulsos_Chuva));
			// Verificar quanto tempo o pino fica em nível alto
        	vTaskDelay(50 / portTICK_PERIOD_MS); // 50ms
			while (digitalRead(PLUVIOMETER_PIN)) {
        vTaskDelay(50 / portTICK_PERIOD_MS); // 50ms;
			}
		}
  vTaskDelay(2 / portTICK_PERIOD_MS);
  }
}

void task_SENSOR_ANEMOMETRO(void *pvParameters){    // OK
  
  while (digitalRead(ANEM_PIN)) {
    vTaskDelay(1);
  }
  
  unsigned long time_last_read = millis();
  while (true) {
    if (digitalRead(ANEM_PIN)) {
      debug("Chegou um pulso de vento, pulsos = " + String(tPulsos_Anemometro_quantidade + 1));
      const auto now = millis();
      const auto tempo_entre_pulsos = now - time_last_read;
      debug("Tempo entre pulsos = " + String(tempo_entre_pulsos) + " > Min = " + String(tPulsos_Anemometro_menor_duracao));

      if (tempo_entre_pulsos < 100) {
        while (digitalRead(ANEM_PIN)) {
          vTaskDelay(1/portTICK_PERIOD_MS);
        }
        continue;
      }

      tPulsos_Anemometro_quantidade++;

      if (tempo_entre_pulsos < tPulsos_Anemometro_menor_duracao) {
        tPulsos_Anemometro_menor_duracao = tempo_entre_pulsos;
      }
      time_last_read = now;
      while (digitalRead(ANEM_PIN)) {
        vTaskDelay(1/portTICK_PERIOD_MS);
      }
    }
    vTaskDelay(2/portTICK_PERIOD_MS);
  }
}





// Inicializa Sensores 

void Inicializa_SENSOR_BME(){           // OK
  
  if (SENSOR_BME.begin(BME280_ADDRESS_ALTERNATE)) {
    flag_SENSOR_BME = true;
  }else {
    flag_SENSOR_BME = SENSOR_BME.begin(BME280_ADDRESS);
  }
  if (flag_SENSOR_BME) {
    debug("    Iniciado - BME280");
  } else {
    debug("Nao Iniciado - BME280");
  }
}

void Inicializa_SENSOR_PLUVIOMETRO(){   // OK
  debug("    Iniciado - Pluviometro");

  xTaskCreate(task_SENSOR_PLUVIOMETRO, "chuva", 20000, NULL, 1, NULL);
}

void Inicializa_SENSOR_ANEMOMETRO(){    // OK
  debug("    Iniciado - Anemometro");

  xTaskCreate(task_SENSOR_ANEMOMETRO, "anemometro", 20000, NULL, 1, NULL);
}

void Inicializa_SENSOR_ADS1115(){       // OK
  debug("    Iniciado - ADS1115");

  if(SENSOR_ADS.begin()){
    debug("    Iniciado - ADS1115");
  }
  else{
    debug("Nao Iniciado - ADS1115");
  }
}

void Inicializa_SENSOR_DS18B20(){       // Completar Funcao (Nao Necessario até agora)
  debug("    Iniciado - DS18B20");

}

void Inicializa_SENSOR_SHT35(){         // Completar Funcao (Nao Necessario até agora)
  debug("    Iniciado - SHT35");
}

void Inicializa_Sensores(){             // OK
  Inicializa_SENSOR_BME();
  Inicializa_SENSOR_PLUVIOMETRO();
  Inicializa_SENSOR_ANEMOMETRO();
  //Inicializa_SENSOR_ADS1115();
  //Inicializa_SENSOR_DS18B20();
  //Inicializa_SENSOR_SHT35();
}





// Leitura de Sensores

void Leitura_SENSOR_BME(){          // OK
  if (flag_SENSOR_BME) {
    Temperatura = SENSOR_BME.readTemperature();
    Pressao = SENSOR_BME.readPressure() / 100.0F;
    Umidade = SENSOR_BME.readHumidity();
  }
}

void Leitura_SENSOR_PLUVIOMETRO(){  // OK
  Chuva = tPulsos_Chuva;
  
  Chuva = Chuva * .2;
}

void Leitura_SENSOR_ANEMOMETRO(){   // OK

  Vento_Media  = 1440 * PI * tPulsos_Anemometro_quantidade/(millis() - Tempo_Ultimo_Envio);
  Vento_Rajada = 1440 * PI / tPulsos_Anemometro_menor_duracao;

}

void Leitura_SENSOR_ADS1115(){      // OK
  /*
  Solar = String(readSolar());
  Anemometro = String(readAnemometro());
  EC5 = String(readEc5());
  SOLO = String(readSolo());
  */
}

void Leitura_Sensores(){            // OK
  debug("Lendo Sensores");
  Leitura_SENSOR_BME();
  Leitura_SENSOR_PLUVIOMETRO();
  Leitura_SENSOR_ANEMOMETRO();
  //Leitura_SENSOR_ADS1115();
  //Leitura_SENSOR_DS18B20();
  //Leitura_SENSOR_SHT35();
}







// WiFi e MQTT

void Recebimento_MQTT(String &topic, String &payload) {   // OK
  Serial.println("incoming: " + topic + " - " + payload);

  // Reiniciar Estacao
  if ((topic == ID_Estacao + "/Interface_Estacao/resetar") && (payload != "0")){
    Mensagem_Reiniciar = true;
    Mensagem_Espere = true;
  }

  // atualiza o firmware
  if ((topic == ID_Estacao + "/Interface_Estacao/atualizar") && (payload != "0")){
    Mensagem_Atualizar = true;
    Versao_Para_Atualizar = payload;
    Mensagem_Espere = true;
  }

  // adiciona uma nova rede ao vetor de redes
  if ((topic == ID_Estacao + "/Interface_Estacao/redes/adicionar") && (payload != "0")){
    Mensagem_rede_adicionar = true;
    Payload_Interface = payload;
    Mensagem_Espere = true;
  }

  // Remove uma rede do vetor de redes
  if ((topic == ID_Estacao + "/Interface_Estacao/redes/remover") && (payload != "0")){
    Mensagem_rede_remover = true;
    Payload_Interface = payload;
    Mensagem_Espere = true;
  }

  // Envia as redes cadastradas
  if ((topic == ID_Estacao + "/Interface_Estacao/redes") && (payload != "0")){
    Mensagem_rede_enviar = true;
    Mensagem_Espere = true;
  }

  // Envia as redes Escaneadas
  if ((topic == ID_Estacao + "/Interface_Estacao/redes/scan") && (payload != "0")){
    Mensagem_rede_scan_enviar = true;
    Mensagem_Espere = true;
  }

  // Envia as redes Escaneadas
  if ((topic == ID_Estacao + "/Interface_Estacao/redes/adicionar_scan") && (payload != "0")){
    Mensagem_rede_scan_adicionar = true;
    Payload_Interface = payload;
    Mensagem_Espere = true;
  }

  
  // Sai da interface
  if ((topic == ID_Estacao + "/Interface_Estacao/sair") && (payload != "0")){
    Mensagem_Espere = false;
  }



  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}
  
void Inicializa_WiFi(){

  WiFi.mode(WIFI_STA);
  WiFi.setHostname(("Estacao Kate " + ID_Estacao).c_str());
	WiFi.setAutoReconnect(true);
  esp_wifi_set_ps(WIFI_PS_NONE);

}

bool Tenta_Conexao_WiFi(const char *SSID,const char *PASS){
  
  WiFi.begin(SSID,PASS);

  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED ) {
    //debug(String(int(WiFi.status())));
    delay(1000);
    debug(".");
    if (tentativas>5){
      return false;
    }
    tentativas++;
  }  
  
  return true;

}

void Conecta_WiFi(){         // OK

  for(rede_atual=0; rede_atual<n_Redes; rede_atual++){
    debug("\nConectando na rede: " + ssid[rede_atual] + ", senha: " + password[rede_atual]);

    // check if the WiFi is connected to the network

    if (!flag_internet_connection[rede_atual]){
      continue;
    }
    if (Tenta_Conexao_WiFi(ssid[rede_atual].c_str(), password[rede_atual].c_str())){
      debug("Conectado ao WiFi");
      esp_wifi_set_ps(WIFI_PS_NONE);
      return;
    }

  }
  for(rede_atual=0; rede_atual<n_Redes; rede_atual++){
    if (!flag_internet_connection[rede_atual]){
      ESP.restart();
    }
  }
  debug("Não Foi Possivel Conectar, entrando no modo de configuracao");
  Configuracao_Local();
  
}

void Inicializa_MQTT(){

  MQTT_Client.setOptions(80, false, 2000);
  MQTT_Client.begin(/*URL DO SERVIDOR MQTT*/, WIFI_Client);
  MQTT_Client.onMessage(Recebimento_MQTT);

}

bool Tenta_Conexao_MQTT(){

  int Tentativas=0;
  
	while(!MQTT_Client.connected()){

		debug("Tentando conectar pela " + String(Tentativas) + " vez");
    if (MQTT_Client.connect(ID_Estacao.c_str(), "esp32" , "senha")){
      return true;
    }
    delay(500);
    if (Tentativas>5){
      return false;
      flag_internet_connection[rede_atual] = false;
    }
    Tentativas++;

  }
  return true;
}

void Conecta_MQTT(){         // OK
  debug("\nConectando ao Broker: ");

  if (MQTT_Client.connected()){
    return;
  }
  while(!Tenta_Conexao_MQTT()){
    while(WiFi.status() != WL_CONNECTED){
      debug("WiFi Desconectado");
      delay(1000);
    }
  }
  
  
  debug("Conectado ao Broker");

  
  MQTT_Client.subscribe(ID_Estacao + "/Interface_Estacao/#",1);
  /*
  MQTT_Client.subscribe(ID_Estacao + "/Interface_Estacao/Reiniciar",1);
  MQTT_Client.subscribe(ID_Estacao + "/Interface_Estacao/Atualizar",1);
  MQTT_Client.subscribe(ID_Estacao + "/Interface_Estacao/redes",1);
  MQTT_Client.subscribe(ID_Estacao + "/Interface_Estacao/redes/adicionar",1);
  MQTT_Client.subscribe(ID_Estacao + "/Interface_Estacao/redes/remover",1);
  MQTT_Client.subscribe(ID_Estacao + "/Interface_Estacao/redes/scan",1);
  MQTT_Client.subscribe(ID_Estacao + "/Interface_Estacao/redes/adicionar_scan",1);
  MQTT_Client.subscribe(ID_Estacao + "/Interface_Estacao/sair",1);
  */
}

bool Publica_MQTT(String Topico, String Dado){

  int Tentativas = 0;

  while(!MQTT_Client.publish((ID_Estacao + Topico).c_str(), Dado,false,2)){
    debug("Enviando " + Topico);
    
    if (Tentativas > 5){
      debug("Falha ao enviar");
      flag_Envio_MQTT = false;
      return false;
    }
    delay(500);
  }
  return true;
}

void Envia_Dados_MQTT(){        // OK
  debug("Enviando dados MQTT");

  if(flag_SENSOR_BME){

    if (!Publica_MQTT("/00/00",String((abs(Temperatura) == inf ? -99 : (Temperatura)))))    return;
    if (!Publica_MQTT("/00/03",String((abs(Umidade) == inf ? -99 : (Umidade)))))            return;
    if (!Publica_MQTT("/00/07",String((abs(Pressao) == inf ? -99 : (Pressao)))))            return;

    debug("\tTemperatura: " + String(Temperatura));
    debug("\tUmidade: " + String(Umidade));
    debug("\tPressao: " + String(Pressao));
  }
  
  int t = millis();
  while (!MQTT_Client.connected()){
    if (millis()-t > 5000){
      debug("Falha ao enviar");
      flag_Envio_MQTT = false;
      return;
    }
  }
  if (!Publica_MQTT("/05/0a",String((abs(Chuva) == inf ? -99 : Chuva))))                    return;
  if (!Publica_MQTT("/08/0f",String((abs(Vento_Media) == inf ? -99 : (Vento_Media)))))      return;
  if (!Publica_MQTT("/08/10",String((abs(Vento_Rajada) == inf ? -99 : (Vento_Rajada)))))    return;
  if (!Publica_MQTT("/03/0e",String((abs(analogRead(BATERIA_PIN) * (0.0037905)) == inf ? -99 : (analogRead(BATERIA_PIN) * (0.0037905))))))  return; // a conta é (AnalogRead() * (3.3 / 4095) * (1270 / 270))
  if (!Publica_MQTT("/07/0d",String((abs(WiFi.RSSI()) == inf ? -999 : (WiFi.RSSI())))))     return;

  
  

  debug("\tChuva: " + String(Chuva));
  debug("\tVento_Media: " + String(Vento_Media));
  debug("\tVento_Rajada: " + String(Vento_Rajada));
  debug("\tBateria: " + String(analogRead(BATERIA_PIN) * (0.0037905)));
  debug("\tRSSI: " + String(WiFi.RSSI()));

  flag_Envio_MQTT = true;

  tPulsos_Chuva -= Chuva;

  debug("Dados enviados com sucesso");

}

void Envia_Dados_Salvos(){      // Pensar ainda em uma maneira de enviar os dados que nao foi possivel enviar

}

void Reestabelece_Conexao(){    // OK

  //debug("Verificando conexao WiFi");

  wifi_ps_type_t wifi_ps_mode;
  esp_wifi_get_ps(&wifi_ps_mode);

  if (wifi_ps_mode == WIFI_PS_MIN_MODEM){
    vTaskDelay(1);
    return;
  }
  
  
  if ((WiFi.status() != WL_CONNECTED) || (!flag_internet_connection[rede_atual])){
    debug("Reconectando ao WiFi");
    Conecta_WiFi();
    if (WiFi.status() != WL_CONNECTED){
      debug("Não Foi Possivel Conectar, entrando no modo de configuracao");
      Configuracao_Local();
    }
  }
  //debug("Conectado ao WiFi");
  

  //debug("Verificando conexao MQTT");
  if (!MQTT_Client.connected()) {
    debug("Reconectando ao MQTT");
    Conecta_MQTT();
  }
  //debug("Conectado ao MQTT");



}

void Atualizacao_OTA(){         // OK
  String file_path = /*URL DO LOCAL ONDE FICA OS ARQUIVOS DE ATUALIZACAO*/;
	file_path += Versao_Para_Atualizar;
	file_path += ".bin";
  debug("Atualizando para o bin: " + file_path);

  
  httpUpdate.setLedPin(GREEN_LED, HIGH);

  // o onStart tem uma funcao lambda dentro dele que envia um MQTT avisando que a atualizacao foi iniciada
  //httpUpdate.onStart(onStartCallback);
  //httpUpdate.onEnd(onEndCallback);
  //httpUpdate.onError(onErrorCallback);

  httpUpdate.rebootOnUpdate(false);
  Publica_MQTT("/Interface_Estacao/atualizar", "0");
  Publica_MQTT("/Interface_Broker/atualizando", "1");

  auto ret = httpUpdate.update(WIFI_Client, file_path);

  //Reestabelece_Conexao();
	if (ret == HTTP_UPDATE_OK){
    debug("Atualização realizada com sucesso");
    Publica_MQTT("/Interface_Broker/atualizando", "0");
    ESP.restart();
  }
  if (ret == HTTP_UPDATE_NO_UPDATES){
    debug("Versao nao encontrada");
    Publica_MQTT("/Interface_Broker/atualizando", "-2");
  }
  if (ret == HTTP_UPDATE_FAILED){
    debug("Falha na Atualizacao");
    Publica_MQTT("/Interface_Broker/atualizando", "-1");
  }
  
}

void InterfaceMQTT(){
  tempoInterface = millis();

  if (Mensagem_Espere){
    debug("Interface Usuario remoto Iniciada");
    
  
    while (Mensagem_Espere){

      if (Mensagem_Reiniciar){
        debug("Reiniciando");
        Publica_MQTT("/Interface_Estacao/resetar", "0");
        delay(5000);
        ESP.restart();

        tempoInterface = millis();
        Mensagem_Reiniciar = false;
      }

      if (Mensagem_Atualizar){
        debug("atualizando");
        Atualizacao_OTA();

        tempoInterface = millis();
        Mensagem_Atualizar = false;
      }

      if (Mensagem_rede_adicionar){
        debug("Adicionando rede");

        Publica_MQTT("/Interface_Estacao/redes/adicionar", "0");
        delay(200);
        
        // adiciona mais uma rede ao vetor de redes, o payload chega no formato SSID,SENHA
        ssid[n_Redes] = Payload_Interface.substring(0, Payload_Interface.indexOf(","));
        password[n_Redes] = Payload_Interface.substring(Payload_Interface.indexOf(",")+1);
        n_Redes++;
        Escrita_F_wifi_Redes();
        debug("Rede adicionada");

        tempoInterface = millis();
        Mensagem_rede_adicionar = false;
      }

      if (Mensagem_rede_remover){
        debug("Removendo rede");
        Publica_MQTT("/Interface_Estacao/redes/remover", "0");
        delay(200);
        
        // remove a rede do vetor de redes, o payload chega na rede a ser removida
        for(int i=Payload_Interface.toInt()-1 ; i<n_Redes-1; i++){
          ssid[i] = ssid[i+1];
          password[i] = password[i+1];
          Escrita_F_wifi_Redes();
          debug("Rede removida");
          break;
        }
        n_Redes--;

        tempoInterface = millis();
        Mensagem_rede_remover = false;
      }

      if (Mensagem_rede_enviar){
        debug("Enviando redes");

        Publica_MQTT("/Interface_Estacao/redes", "0");
        for(int i=0 ; i<n_Redes ; i++){
          debug("Enviando a Rede " + String(i) + ": " + ssid[i] + "," + password[i]);
          Publica_MQTT("/Interface_Broker/redes/SSID_Senha/" + String(i+1), ssid[i] + "," + password[i]);
          delay(100);
        }
        debug("Redes enviadas");

        tempoInterface = millis();
        Mensagem_rede_enviar = false;
      }

      if (Mensagem_rede_scan_enviar){

        debug("Enviando redes escaneadas");
        n_Redes_Disponiveis = WiFi.scanNetworks(false);

        for(int i=0; i<n_Redes_Disponiveis; i++) {
          debug("Enviando a Rede " + String(i) + ": " + WiFi.SSID(i) + ", " + WiFi.RSSI(i) + "dBm");
          Publica_MQTT("/Interface_Broker/redes/SSID_Scan/" + String(i+1), WiFi.SSID(i) + ", " + WiFi.RSSI(i) + "dBm");
        }
        
        Publica_MQTT("/Interface_Estacao/redes", "0");
        debug("Redes enviadas");

        tempoInterface = millis();
        Mensagem_rede_scan_enviar = false;
      }

      if (Mensagem_rede_scan_adicionar){
        debug("Adicionando rede escaneada");

        delay(200);
        
        // adiciona mais uma rede ao vetor de redes, o payload chega no formato SSID,SENHA

        ssid[n_Redes] = WiFi.SSID((Payload_Interface.substring(0, Payload_Interface.indexOf(","))).toInt()-1);
        password[n_Redes] = Payload_Interface.substring(Payload_Interface.indexOf(",")+1);
        n_Redes++;
        Escrita_F_wifi_Redes();
        debug("Rede adicionada");

        
        Publica_MQTT("/Interface_Estacao/redes/adicionar_scan", "0");
        tempoInterface = millis();
        Mensagem_rede_adicionar = false;
      }

      if ((millis() - tempoInterface) % 10000 < 2){
        Publica_MQTT("/Interface_Broker/timeout", String(30 - (millis() - tempoInterface) / 1000) + "s");
      }

      if (millis() - tempoInterface > 30000){
        Mensagem_Espere = false;
        debug("timeout de conexao");
      }

    }
    
    debug("Fechando interface...");
    Publica_MQTT("/Interface_Estacao/sair", "0");
  }
}

void Leitura_Hora_Web(){
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  int t_Momento_Aquisicao = millis();
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  rtc.setTimeStruct(timeinfo);

  // mostra a data e hora atual na serial através do debug
  debug(rtc.getTime("%d%m%Y%H%M%S"));
  //debug(rtc.getTime("%A, %B %d %Y %H:%M:%S"));

}

void task_Reconexao(void *pvParameters){
  
  Inicializa_WiFi();
  Inicializa_MQTT();

  while(true){
    Reestabelece_Conexao();   // OK
    vTaskDelay(2);
  }

}

bool Espera_Conexao(){
  esp_wifi_set_ps(WIFI_PS_NONE);

  int t = millis();
  while(!(WiFi.status() == WL_CONNECTED) || !(MQTT_Client.connected())){
    delay(100);

    if (millis() - t > 5000){ // 5 segundos
      debug("timeout de conexao");
      return false;
    }
  }
  return true;
}







// Main

void setup() {              // OK
  
  Inicializa_Placa();       // OK
  Leitura_SPIFFS();         // OK
  if (digitalRead(DEBUG_PIN) == LOW){
    Configuracao_Local();
  }

  xTaskCreate(task_Reconexao, "Reconexao", 20000, NULL, 1, NULL);

  Inicializa_Sensores();    // OK
  //Leitura_Relatorio_Info(); // OK



}

void loop() {               // OK

  digitalWrite(YELLOW_LED, HIGH);
  
  Leitura_Sensores();       // OK
  if (!Espera_Conexao()){return;}
  Envia_Dados_MQTT();       // OK

  Pisca_Leds();             // OK
  InterfaceMQTT();          // OK
  
  esp_wifi_set_ps(WIFI_PS_MIN_MODEM);

  digitalWrite(YELLOW_LED, LOW);
  delay(59000);             // OK
}

