#include <IOXhop_FirebaseESP32.h>
#include <IOXhop_FirebaseStream.h>

#include <WiFi.h>

#include <ArduinoJson.h>

//Definindo pino dos sensores e atuadores
#define Trigger 13
#define Echo 12
#define Pir 27
#define Ir  25
#define Buzzer 13
#define Lampada 14

//Variáveis de controle
float distancia;//Variável que armazena o valor lido pelo US
int EstadoIr;//0 = Objeto detectado ; 1 = Nada detectado
bool EstadoPir; //0 = Sem movimento ; 1 = Com movimento 

//Senhas para o nível 4
String senhaSistem;//Definida no sistema
String senha; //Digitada pelo invasor


#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

void setup() {
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Ir, INPUT);
  pinMode(Pir, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Lampada, OUTPUT);
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

  Serial.println("Registe uma senha:");

  while(true){//Cadastrar uma senha.
  if(Serial.available()){
  senhaSistem=Serial.readString();
  Serial.print("A senha registrada foi:");
  Serial.println(senhaSistem);
  Firebase.setString("/Cofre/Senha_Master", senhaSistem);
  delay(1000);
  break;}}
}

void loop() {
  delay(10);

  Nivel01();
  if(EstadoIr==0){
  Nivel02();}

  if(EstadoIr==0 && distancia <=20){
  Nivel03();}

  if(EstadoIr==0 && distancia <=20 && EstadoPir == 1){
  Nivel04();}
}

void Nivel01(){
  Serial.println();
  EstadoIr = digitalRead(Ir);
  Serial.println(" ------ Sensores ------");
  if(EstadoIr==0){
  Serial.println("      Estado IR = 0        ");
  Serial.println("     Nível 1 violado       ");
  Serial.println();
  Serial.println(" ----------------------");
  Serial.println();
  Firebase.setString("/Niveis_e_atuadores/Nivel01", "Violado");
  delay(1000);
  }
  else{
  Serial.println();
  Serial.println("       Nada violado       ");
  Serial.println();
  Serial.println(" ----------------------");
  Serial.println();
  Firebase.setString("/Niveis_e_atuadores/Nivel01", "Não violado");
  Firebase.setString("/Niveis_e_atuadores/Nivel02", "Não violado");
  Firebase.setString("/Niveis_e_atuadores/Nivel03", "Não violado");
  delay(1000);
  }
}

void Nivel02(){
  //tirar
  while(true){//Cadastrar uma senha.
  Serial.println("Registre a distancia:");
  if(Serial.available()){
  distancia = Serial.parseFloat();
  Serial.print("A distancia registrada foi:");
  Serial.println(distancia);
  delay(1000);
  break;}}
  //até aqui

  //distancia = Ultrasonic(Trigger, Echo);//Determina a variável por meio da função
  if (distancia <=20){

  Serial.println(" ------ Sensores ------");
  Serial.println("      Estado IR = 0        ");
  Serial.print("    Distância = ");
  Serial.print(distancia);
  Serial.println("Cm       ");
  Serial.println("   Nível 1 e 2 violados     ");
  Serial.println();
  Serial.println(" ----------------------");
  Serial.println();
  Firebase.setString("/Niveis_e_atuadores/Nivel02", "Violado");
  delay(1000);
  }
  else{Firebase.setString("/Niveis_e_atuadores/Nivel02", "Não violado");}
}

void Nivel03(){
  EstadoPir = digitalRead(Pir);
  if(EstadoPir == 1){
  Serial.println(" --------- Sensores ---------");
  Serial.println("        Estado IR = 0        ");
  Serial.print("      Distância = ");
  Serial.print(distancia);
  Serial.println("Cm");
  Serial.println("        Estado Pir = 1        ");
  Serial.println(" Níveis 1, 2 e 3 comprometidos");
  Serial.println();
  Serial.println(" -----------------------------");
  Serial.println();
  Firebase.setString("/Niveis_e_atuadores/Nivel03", "Violado");
  delay(2000);
  }
  else{Firebase.setString("/Niveis_e_atuadores/Nivel03", "Não violado");}
}

void Nivel04(){//Função cofre
  Serial.println("Digite sua senha.");

  while(true){

  if(Serial.available()){
  senha=Serial.readString();{
  Serial.print("A senha digitada foi:");
  Serial.println(senha);
  Firebase.setString("/Cofre/Senha_Digitada", senha);
  delay(500);
  if(senha==senhaSistem){
  Serial.println("Senha correta");
  digitalWrite(Buzzer, 0);
  digitalWrite(Lampada, 1);
  Firebase.setString("/Niveis_e_atuadores/Nivel04/Buzzer", "Desligado");
  Firebase.setString("/Niveis_e_atuadores/Nivel04/Lampada", "Ligada");
  delay(5000);
  digitalWrite(Lampada, 0);
  Firebase.setString("/Niveis_e_atuadores/Nivel04/Buzzer", "Desligado");
  Firebase.setString("/Niveis_e_atuadores/Nivel04/Lampada", "Desligada");
   break;}
  else{
  Serial.println("Senha incorreta");
  digitalWrite(Buzzer, 1);
  digitalWrite(Lampada, 0);
  Firebase.setString("/Niveis_e_atuadores/Nivel04/Buzzer", "Ligado");
  Firebase.setString("/Niveis_e_atuadores/Nivel04/Lampada", "Desligada");
  delay(5000);
  digitalWrite(Buzzer, 0);
  Firebase.setString("/Niveis_e_atuadores/Nivel04/Buzzer", "Desligado");
  Firebase.setString("/Niveis_e_atuadores/Nivel04/Lampada", "Desligada");
  break; }
  }
  }

  }
}

float Ultrasonic(int pintrigger, int pinecho){//Função para definir a distancia do sensor
  int distancia = 0;//define um valor para travar na função (entrar no while)
  while(distancia == 0) {
    digitalWrite(pintrigger, 0);//Desliga o trigger
    delayMicroseconds(5);
    digitalWrite(pintrigger, 1);//Liga o trigger
    delayMicroseconds(5);
    float tempo = pulseIn(pinecho,1);//Conta o tempo entre a saida e chegada do pulso
    distancia = (tempo/2/29.15);//Joga esse tempo numa formula e determina a distancia
  }
  return distancia;
}