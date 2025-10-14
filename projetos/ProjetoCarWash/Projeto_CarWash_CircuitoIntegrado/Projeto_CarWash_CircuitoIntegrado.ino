int emergencia=0;//Variável que gerencia o botão de emergência
void setup(){
	pinMode(13, OUTPUT);//Motores da esteira
  //Leds
  pinMode(23, OUTPUT);//Led de emergência
  pinMode(22, OUTPUT);//Led de espera
    //Entrada dos sensores
	pinMode(34, INPUT);
	pinMode(35, INPUT);
	pinMode(32, INPUT);
	pinMode(33, INPUT);
  pinMode(25, INPUT);
    //Saída dos sensores aos motores
	pinMode(26, OUTPUT);//M1
	pinMode(27, OUTPUT);//M2
	pinMode(14, OUTPUT);//M3
	pinMode(12, OUTPUT);//M4
    //Entrada para a saída do CI para controle do botão de emergência
  pinMode(39, INPUT);
    
    //Botão de inicialização
	pinMode(36, INPUT_PULLUP);
	
}	

void loop(){

    digitalWrite(22, 1);//Liga o led de espera
    
  while(digitalRead(36)==0){//While para funcionamento padrão
    digitalWrite(22, 0);//Desliga o led de espera
    
    while(true){
    
    digitalWrite(13, 1);
      
    if(digitalRead(39)==1)//Leva o veículo para o fim do lava jato em caso de emergência
    {
      while(digitalRead(39)==1){}//Impede comandos infinitos
      emergencia=1;//Emergencia ativa
      while(digitalRead(39)!=1){
      if(emergencia==1){
      digitalWrite(23, 1);//Liga o led de emergência.
      func_motores(1,0,0,0,0,0);}//Desliga todos os motores menos a esteira
      }
      emergencia=0;
      digitalWrite(23, 0);//Desliga o led de emergência.
    
    }
      
    if(digitalRead(34) == 1){//Sensor1, O pino 5 da esp(RDX) é normalmente alto
   digitalWrite(23,1);
    }
    else if(digitalRead(35) == 1){
	 func_motores(0,0,1,0,0,3000);
    }
    else if(digitalRead(32) == 1){
	 func_motores(0,0,0,1,0,500);
    }
    else if(digitalRead(33) == 1){
	 func_motores(0,0,0,0,1,1000);
    }
  	else if(digitalRead(25) == 1){//Sensor5
	 func_motores(0,0,0,0,0,0);
     break;//Para tudo (quando normal)
    }
                  }//Fim while true
     digitalWrite(13, 0);//Desliga a esteira
  }
 
}//Final void loop

//Função que liga ou desliga os motores
int func_motores(int esteira, int M1, int M2, int M3, int M4, int D)
{
    digitalWrite(13, esteira);//Desliga a esteira momentaneamente
    digitalWrite(26, M1);
    digitalWrite(27, M2);
    digitalWrite(14, M3);
    digitalWrite(12, M4);
    delay(D);
    digitalWrite(13, 1);//Liga novamente a esteira
    return 0;
}
