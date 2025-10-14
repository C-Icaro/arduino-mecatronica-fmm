

#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>

#include <WiFi.h>

#include <ArduinoJson.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

//Microfone
const int microphonePin = 25;

//Fitas
#define Fita1 26
#define Fita2 27
#define Mesa  14
bool modo1=false, modo2=false;

//DHT
#include <dht11.h>
#define DHT11PIN 12
dht11 DHT11;


/*
Atuadores:
Lampada da Sala - Fita Led
Lampada da Cozinha - Fita Led
Mesa de Dominó - Jogo
Motor DC - 

Ponte H com potenciometro


Imputs:
Comando de voz - I2S
Temperatura do Ambiente
Umidade do Ambiente


Integrações:
Interface usuário máquina por VS
Comando de voz
Integração com Firebase

Telas:
Tela de Login e cadastro
Tela de leitura de dados
Tela de Atuadores

*/


void setup() {

  pinMode(Fita1, OUTPUT);
  pinMode(Fita2, OUTPUT);
  pinMode(Mesa, OUTPUT);
  Serial.begin(115200);


}

void loop() {

  //Func_Voz();
  int mn = 1024;
  int mx = 0;
  for (int i = 0; i < 10000; ++i) {

    int val = analogRead(microphonePin);
    mn = min(mn, val);
    mx = max(mx, val);
  }

  
  DHT();

  Func_Atuadores();
 

}


void Func_Voz(){
  int mn = 1024;
  int mx = 0;


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
    delay(300);
    
  }
   if(788 < mx & mx < 1077){//Calculado pela média e desvio padrão de 12 números - 933 e 145 respectivamente
    modo2=!modo2;
    //Firebase.setBool("/Atuadores/Fita_Quarto", modo2);
    digitalWrite(Fita2, modo2);
    delay(300);
  }
}


void Func_Atuadores(){
  
  
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   Serial.println("Conectando ao WiFi");
  
   Func_Voz();
    Serial.println("Teste0");
   while(WiFi.status()!= WL_CONNECTED){
     Serial.print("Conectando...");
     Serial.println();
     delay(1000);
    }
    Serial.println();
    Serial.print("Conectado");
    Serial.println();
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);


  Firebase.setBool("/Atuadores/Fita_Sala", modo1);
  Firebase.setBool("/Atuadores/Fita_Quarto", modo2);
  

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
    Serial.print("Passou por ELSE_Quarto:");
    Serial.println(F2);}

  bool M = Firebase.getBool("/Atuadores/Mesa");
  if(M == true ){
    digitalWrite(Mesa, M);
    Serial.println("Passou por IF_Mesa");
  }
  else{
    digitalWrite(Fita2, F2);
    Serial.print("Passou por ELSE_Mesa:");
    Serial.println(M);}


    WiFi.disconnect();
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

  delay(200);

}