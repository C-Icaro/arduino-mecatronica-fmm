#include <Wire.h>

#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>

#include <WiFi.h>

#include <ArduinoJson.h>

/*#define WIFI_SSID "CI - M3A"
#define WIFI_PASSWORD "12345678"
#define FIREBASE_HOST "https://macroprojetodsi-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "CItpeFcHBu1q6LXRR5MFLJ1o6Y8Zl-quCWS1jmJVV04"*/

//Microfone
const int microphonePin = 25;
#define Fita1 26
#define Fita2 27
bool modo1=false, modo2=false;





void setup() {

  pinMode(Fita1, OUTPUT);
  pinMode(Fita2, OUTPUT);
  Serial.begin(115200);

   /*WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
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
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);*/

}

void loop() {
  Func_Voz();
 

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
