#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>

#include <WiFi.h>
#include <ArduinoJson.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

String Nome, Setor, Data;
int Matricula, Turno;
void setup() {
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

    Serial.println("Digite 'Cadastro'");
    while(true){
    if(Serial.available()){
    Serial.readString();
    Func_Cadastro();
    Serial.println("Cadastro Finalizado");
    break;
    }
    }
}

void loop() {



}


void Func_Cadastro()
{
  Serial.read();
  Serial.flush();
  Serial.print("Digite o seu nome:");
  while(true)
  {if (Serial.available()){
    Nome = Serial.readString();
    Serial.println(Nome);
    Firebase.setString("/Cadastro User/Nome", Nome);
    break;
    }
  }
  Serial.read();
  Serial.print("Digite a sua matrícula sem espaços:");
   while(true)
  {if (Serial.available()){
    Matricula = Serial.parseInt();
    Serial.println(Matricula);
    Firebase.setInt("/Cadastro User/Matricula", Matricula);
    break;
    }
  }
  Serial.read();
  Serial.print("Digite a data de operação do processo (xx-xx):");
   while(true)
  {if (Serial.available()){
    Data = Serial.readString();
    Serial.println(Data);
    Firebase.setString("/Cadastro User/Data", Data);
    break;
    }
  }
  Serial.read();
  Serial.print("Digite o seu setor (Materiais, Manutenção ou Produção):");
   while(true)
  {if (Serial.available()){
    Setor = Serial.readString();
    Serial.println(Setor);
    Firebase.setString("/Cadastro User/Setor", Setor);
    break;
    }
  }
  Serial.read();
  Serial.print("Digite o seu turno (1 ou 2):");
   while(true)
  {if (Serial.available()){
    Turno = Serial.parseInt();
    Serial.println(Turno);
    Firebase.setInt("/Cadastro User/Turno", Turno);
    break;
    }
}
}