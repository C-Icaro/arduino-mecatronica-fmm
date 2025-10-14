

#define Trigger 15
#define Echo 2
#define Pin3 4//Led verde
#define Pin4 21//Led Amarelo
#define Pin5 18//Sensor PIR
#define Pin6 19//Led 3
#define buzzer 22//Buzzer
float distancia;//Variável que armazena o valor lido pelo US


String senha;
String senhaSistem;


void setup()
{
    Serial.begin(115200);
    pinMode(Trigger, OUTPUT);
    pinMode(Echo, INPUT);
    pinMode(Pin3, OUTPUT);
    pinMode(Pin4, OUTPUT);
    pinMode(Pin5, INPUT);
    pinMode(Pin6, OUTPUT);
    pinMode(buzzer, OUTPUT);

  Serial.println("Registe uma senha de 4 caracteres:");

  while(true){//Cadastrar uma senha.
  if(Serial.available()){
  senhaSistem=Serial.readString();{
  Serial.print("A senha registrada foi:");
  Serial.println(senhaSistem);
  delay(1000);
  break; }}
  }
}

void loop()
{
    Serial.print("Distancia:");
    distancia = Ultrasonic(Trigger,Echo);//Determina a variável por meio da função
    Serial.print(distancia);
    Serial.println("Cm");
    Serial.print("Nível lógico PIR:");
    Serial.println(digitalRead(Pin5));
    delay(2000);

    if(distancia<=100)//If dentro do raio do US
    {
      
      for(int i = 0; i <= 5; i++)//O Led amarelo piscará por 10segundos
      {
      digitalWrite(Pin4,1);
      delay(500);
      digitalWrite(Pin4,0);
      delay(500);
      }

      if(digitalRead(Pin5)==1)//If dentro do raio do PIR
      {

      for(int i = 0; i <= 5; i++)//O Led Vermelho piscará por 10segundos
      {
      digitalWrite(Pin3,1);
      delay(500);
      digitalWrite(Pin3,0);
      delay(500);
      }

      Func_Cofre();

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

void Func_Cofre(){//Função cofre
  Serial.println("Digite sua senha.");

  while(true){

  if(Serial.available()){
  senha=Serial.readString();{
  Serial.print("A senha digitada foi:");
  Serial.println(senha);
  delay(1000);
  if(senha==senhaSistem){
  Serial.println("Senha correta");
  digitalWrite(buzzer, 1);
  digitalWrite(Pin6, 1);
  delay(2000);
  digitalWrite(buzzer, 0);
  digitalWrite(Pin6, 0);
   break;}
  else{
  Serial.println("Senha incorreta");

  for(int i = 0; i <= 5; i++){//O Led 3 e o buzzer piscarão por 5 seg
      digitalWrite(buzzer, 1);
      digitalWrite(Pin6, 1);
      delay(500);
      digitalWrite(buzzer, 0);}
      digitalWrite(Pin6, 0);
      
      break; }
  }
  }
  
  }

 
}