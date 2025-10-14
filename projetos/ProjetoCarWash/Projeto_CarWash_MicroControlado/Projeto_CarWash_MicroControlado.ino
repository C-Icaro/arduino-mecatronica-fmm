int Pin0=15;//B0
int Pin1=2;//BE
int Pin2=33;//S4
int Pin3=32;//S3
int Pin4=35;//S2
int Pin5=34;//S1
int Pin6=12;//M4
int Pin7=14;//M3
int Pin8=27;//M2
int Pin9=26;//M1
int Pin10=25;//S5
int Pin11=22;//LedVerde
int Pin12=23;//LedVermelho
int Pin13=13;//Esteira

int emergencia=0;//Variável que gerencia o botão de emergência
void setup(){
	pinMode(Pin13, OUTPUT);//Motores da esteira
    pinMode(Pin12, OUTPUT);//Led de emergência
    pinMode(Pin11, OUTPUT);//Led de espera
    //Entrada dos sensores
	pinMode(Pin10, INPUT);
	pinMode(Pin2, INPUT);
	pinMode(Pin3, INPUT);
	pinMode(Pin4, INPUT);
    pinMode(Pin5, INPUT);
    //Saída dos sensores
	pinMode(Pin6, OUTPUT);
	pinMode(Pin7, OUTPUT);
	pinMode(Pin8, OUTPUT);
	pinMode(Pin9, OUTPUT);
    //Entrada para a saída do CI para controle do botão de emergência
  	pinMode(Pin1, INPUT);
  
    //Botão de inicialização
	pinMode(Pin0, INPUT_PULLUP);


   //Pino de teste
  pinMode(19, OUTPUT); 
	
}	

void loop(){
    
  
    digitalWrite(Pin11, 1);//Liga o led de espera
    digitalWrite(19,1);
  
  while(digitalRead(Pin0)==0){//While para funcionamento padrão
    digitalWrite(Pin11, 0);//Desliga o led de espera
    while(true){
    digitalWrite(Pin13, 1);
    inicio:
    if(digitalRead(Pin1)==1)//Leva o veículo para o fim do lava jato em caso de emergência
    {
      while(digitalRead(Pin1)==1){}//Impede comandos infinitos
      emergencia=1;//Emergencia ativa
      while(digitalRead(Pin1)!=1){
      if(emergencia==1){
      digitalWrite(Pin12, 1);//Liga o led de emergência.
      func_motores(1,0,0,0,0,0);}//Desliga todos os motores menos a esteira

      }
      digitalWrite(Pin12, 1);//Liga o led de emergência.
      digitalWrite(Pin13, 1);
      delay(15000);
      digitalWrite(Pin13, 0);
      emergencia=0;
      digitalWrite(Pin12, 0);//Desliga o led de emergência.
      break;
    }
      
    //Orquestramento:
    digitalWrite(13,1);
    delay(5000);
    digitalWrite(Pin9, 1);
    if(digitalRead(Pin1)==1){goto inicio;}
    delay(3000);
    digitalWrite(Pin9, 0);
    delay(3000);
    digitalWrite(Pin8, 1);
    if(digitalRead(Pin1)==1){goto inicio;}
    delay(3000);
    digitalWrite(Pin8, 0);
    delay(3000);
    digitalWrite(Pin7, 1);
    if(digitalRead(Pin1)==1){goto inicio;}
    delay(3000);
    digitalWrite(Pin7, 0);
    delay(3000);
    digitalWrite(Pin6, 1);
    if(digitalRead(Pin1)==1){goto inicio;}
    delay(3000);
    digitalWrite(Pin6, 0);
    break;
                  }//Fim while true
     digitalWrite(Pin13, 0);//Desliga a esteira
  }
 
}//Final void loop

//Função que liga ou desliga os motores
int func_motores(int esteira, int M1, int M2, int M3, int M4, int D)
{
    digitalWrite(Pin13, esteira);//Desliga a esteira momentaneamente
    digitalWrite(Pin9, M1);
    digitalWrite(Pin8, M2);
    digitalWrite(Pin7, M3);
    digitalWrite(Pin6, M4);
    delay(D);
    digitalWrite(Pin13, 1);//Liga novamente a esteira
    return 0;
}
