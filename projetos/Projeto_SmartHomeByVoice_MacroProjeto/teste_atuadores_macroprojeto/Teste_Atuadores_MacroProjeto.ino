#include <Wire.h>

#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>

#include <WiFi.h>

#include <ArduinoJson.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

#define Fita1 26
#define Fita2 27




void setup() {

  pinMode(Fita1, OUTPUT);
  pinMode(Fita2, OUTPUT);
  Serial.begin(115200);

   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   Serial.println("Conectando ao WiFi");
   while(WiFi.status()!= WL_CONNECTED){
     Serial.print("Conectando...");
     Serial.println();
     delay(1000);
    }
    Serial.println();
    Serial.print("Conectado");
    Serial.println();
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);

}

void loop() {
  //Colocar um if firebase_get(...) =! N ----> Somente entra na função se tiver alguma mudança (Tipo Serial.available)

    



  Func_Atuadores();

}


void Func_Atuadores(){
  
bool F1 = Firebase.getBool("/Atuadores/Fita_Sala");
  if(F1 == true){

    Serial.println("Passou por IF_SALA");
  }
  else{
  
    Serial.println("Passou por ELSE_SALA");

  }

  bool F2 = Firebase.getBool("/Atuadores/Fita_Quarto");
  if(F2 == true ){

    Serial.println("Passou por IF_QUARTO");
  }
  else{
  
    Serial.println("Passou por ELSE_QUARTO");

  }


}

