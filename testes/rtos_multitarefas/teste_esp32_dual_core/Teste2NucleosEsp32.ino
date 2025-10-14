

#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>

#include <WiFi.h>

#include <ArduinoJson.h>


//Microfone
const int microphonePin = 25;

//Fitas
#define Fita1 26
#define Fita2 27
bool modo1=false, modo2=false;

//DHT
#include <dht11.h>
#define DHT11PIN 12
dht11 DHT11;



TaskHandle_t Task1;
TaskHandle_t Task2;

void setup() {
  Serial.begin(115200);
  
  // Cria a tarefa 1 no núcleo 0
  xTaskCreatePinnedToCore(
    readSensorTask,   // Função da tarefa
    "ReadSensorTask", // Nome da tarefa
    10000,            // Tamanho da pilha da tarefa
    NULL,             // Parâmetro da tarefa
    1,                // Prioridade da tarefa
    &Task1,           // Handle da tarefa
    0                 // Núcleo ao qual a tarefa está associada
  );

  // Cria a tarefa 2 no núcleo 1
  xTaskCreatePinnedToCore(
    manageWiFiTask,   // Função da tarefa
    "ManageWiFiTask", // Nome da tarefa
    10000,            // Tamanho da pilha da tarefa
    NULL,             // Parâmetro da tarefa
    1,                // Prioridade da tarefa
    &Task2,           // Handle da tarefa
    1                 // Núcleo ao qual a tarefa está associada
  );
}

void loop() {
  // O loop() pode ficar vazio, pois estamos usando tarefas FreeRTOS
}

// Função da tarefa de leitura do sensor
void readSensorTask(void * parameter) {
  Func_Voz();
}

// Função da tarefa de gerenciamento do WiFi
void manageWiFiTask(void * parameter) {

   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   Serial.println("Conectando ao WiFi");
  
   Func_Voz();
    Serial.println("Teste0");
   while(WiFi.status()!= WL_CONNECTED){
     Serial.print("Conectando...");
     Serial.println();
     vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    Serial.println();
    Serial.print("Conectado");
    Serial.println();
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);

    while(true){DHT();

  Func_Atuadores();}
}


void Func_Atuadores(){
bool F1 = Firebase.getBool("/Atuadores/Fita_Sala");
  if(F1 == true){
    digitalWrite(Fita1, F1);
    Serial.println("Passou por IF_SALA");
  }
  else{
    digitalWrite(Fita1, F1);
    Serial.print("Passou por ELSE_SALA:");
     Serial.println(F1);}

  bool F2 = Firebase.getBool("/Atuadores/Fita_Quarto");
  if(F2 == true ){
    digitalWrite(Fita2, F2);
    Serial.println("Passou por IF_QUARTO");
  }
  else{
    digitalWrite(Fita2, F2);
    Serial.print("Passou por ELSE_QUARTO:");
    Serial.println(F2);}
}


void Func_Voz(){
  int mn = 1024;
  int mx = 0;
   
  /*while(true){
    digitalWrite(Fita1, modo1);
    delay(500);
    modo1=!modo1;
    digitalWrite(Fita1, modo1);
    delay(500);}
  */
  for (int i = 0; i < 10000; ++i) {

    int val = analogRead(microphonePin);
    
    mn = min(mn, val);
    mx = max(mx, val);
  }

  int val = analogRead(microphonePin);
  int delta = mx - mn;

  Serial.print("Min=");
  Serial.print(mn);
  Serial.print(" Max=");
  Serial.print(mx);
  Serial.print(" Delta=");
  Serial.print(delta);
  Serial.print(" Val=");
  Serial.println(val);


  
  if(619< mx & mx < 723){//Calculado pela média e desvio padrão de 16 números - 656 e 37 respectivamente
    modo1=!modo1;
    digitalWrite(Fita1, modo1);
    //Firebase.setBool("/Atuadores/Fita_Sala", modo1);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    
  }
   if(788 < mx & mx < 1077){//Calculado pela média e desvio padrão de 12 números - 933 e 145 respectivamente
    modo2=!modo2;
    //Firebase.setBool("/Atuadores/Fita_Quarto", modo2);
    digitalWrite(Fita2, modo2);
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void DHT(){
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  float Hum = DHT11.humidity;
  Firebase.setInt("/Dados_Sensores/Humidade", Hum);
  Serial.println(Hum);


  Serial.print("Temperature  (C): ");
  float Temp = DHT11.temperature;
  Firebase.setInt("/Dados_Sensores/Temperatura", Temp);
  Serial.println(Temp);

  vTaskDelay(500 / portTICK_PERIOD_MS);

}