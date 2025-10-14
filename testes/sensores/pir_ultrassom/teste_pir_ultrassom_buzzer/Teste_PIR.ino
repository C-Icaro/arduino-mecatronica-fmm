#define lgreen 12
#define red 32
#define purple 14
#define trigger 18
#define echo 19
#define buzzer 15
float distancia;
#define sensorpir 26
String senhaCadastrada;
String senhaDigitada;

void setup()
{
  Serial.begin(115200);
  pinMode(trigger, OUTPUT); // trigger
  pinMode(echo, INPUT); //echo
  pinMode(red, OUTPUT);
  pinMode(purple, OUTPUT);
  pinMode(sensorpir,INPUT);
  pinMode(lgreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
 
  Serial.println("Cadastre uma senha de 4 caracteres:");
  while(true){
  if(Serial.available()){
  senhaCadastrada = Serial.readString();
 
  Serial.println("A senha cadastrada foi:");
  Serial.println(senhaCadastrada);
  delay(3000);
  break;
  }
 
  }
   
  loop();
  }

void loop()
{
  Serial.print("distancia: ");
  distancia = Ultrasonic(trigger,echo);
  delay(10);
  Serial.print(distancia);
  Serial.println("cm");
  delay(1000);

  int leitorpir = digitalRead(sensorpir);
  Serial.print("Nivel logico PIR: ");
  Serial.println(leitorpir);
  delay(1000);

  if (distancia <= 100)
  {
   digitalWrite(red, HIGH);
   delay(3000);
   while(true)
   {
   
     if (distancia <= 100 && leitorpir == HIGH){
     digitalWrite(purple, HIGH);
     delay(3000);
      while(true)
      {
      Serial.println("Digite sua senha:");
      while(true)
      {
       if(Serial.available())
       {
       senhaDigitada = Serial.readString();
       Serial.println("A senha digitada foi:");
       Serial.println(senhaDigitada);
       break;
       }
      }
       if(senhaDigitada == senhaCadastrada)
       {
        Serial.println("Senha Correta");
         for(int i = 0; i <= 3; i++)
         {
           tone (buzzer, 800, 500);
          digitalWrite(lgreen, HIGH);
          delay(500);
          digitalWrite(lgreen, LOW);
          delay(500);

         }
      }
       else
       {
            Serial.println("Senha Incorreta");
           tone (buzzer, 250, 2000);
            delay(1000);
       }
        break;

      }
      digitalWrite(red, LOW);
      digitalWrite(purple, LOW);
   
   }
   }
   }

 
 }
 
     
 float Ultrasonic(int pintrigger, int pinecho){
  int distancia = 0;
  while(distancia == 0) {
    digitalWrite(pintrigger, 0);
    delayMicroseconds(5);
    digitalWrite(pintrigger, 1);
    delayMicroseconds(5);
    float tempo = pulseIn(pinecho,1);
    distancia = (tempo/2/29.15);
  }
  return distancia;
}