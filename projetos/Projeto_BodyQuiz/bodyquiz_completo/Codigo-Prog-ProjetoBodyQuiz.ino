#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,4);  // set the LCD address to 0x20 for a 16 chars and 4 line display

int Pin[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10};//Array pino dos botões
int Tamanho = sizeof(Pin) / sizeof(Pin[0]);//Calcula o tamanho do array

int modoJogoIndex = 0;//Guarda a posição do modo de jogo
char modoJogo[][20] = {"Aprendizado", "Desafio Solo", "Desafio Dupla"};//Guarda o nome dos modos de jogo
bool escolhido = false;
unsigned long time;//Variável de tempo para a função millis

long iRepetido; //Controle do random question

// Array perguntas em forma de ponteiro
  char *perguntas[] = {
    "Bombeia sangue para o corpo?",
    "Troca de oxigenio por CO2?",
    "Filtra sangue e armazena celulas sanguineas?",
    "Produz bile e desintoxica?",
    "Digere alimentos com acidos?",
    "Filtra sangue e produz urina?",
    "Absorve nutrientes dos alimentos?",
    "Produz insulina e regula acucar?"
    };

  // Array respostas em forma de ponteiro
  char *respostas[] = {
    "Coracao",
    "Pulmoes",
    "Baco",
    "Figado",
    "Estomago",
    "Rins",
    "Intestinos",
    "Pancreas"
    };

  int totalPerguntas = sizeof(perguntas) / sizeof(perguntas[0]); // Conta quantas perguntas existem
  int ultimaPergunta = -1; // Índice da pergunta atual
  int indiceAleatorio; //Indice da pergunta printada no lcd

  int quantidadePinos = sizeof(Pin) / sizeof(Pin[0]);


void setup()
{
  lcd.init();// Inicializa o LCD
  Serial.begin(9600);
   Serial.println("Serial Iniciada.");

  for(int i = 0; i <= Tamanho; i++){//Definição do PinMode de todos os botões
    pinMode(Pin[i], INPUT_PULLUP);
  }
  lcd.backlight();
  lcd.print("Bem vindo ao projeto");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Escolha um modo:");
  lcd.setCursor(0,1);
  lcd.print(modoJogo[modoJogoIndex]);
  lcd.setCursor(0,3);
  lcd.print(modoJogoIndex);

  
}

void loop()
{
  /*
  for(int i = 0; i < Tamanho; i++){//For para verificação de funcionamento dos botões
    while(digitalRead(Pin[i]) == 0){
    lcd.setCursor(0,1);
    lcd.print("Botão pressionado:");
    lcd.print(i);}
    lcd.clear();
  }
  */
  funcModoJogo();
  
}


void funcModoJogo(){

  if(digitalRead(Pin[0]) == 0){

    time = millis();//Pareia a variável time com a função millis

    while(digitalRead(Pin[0]) == 0 && escolhido == false){//Impede comandos infinitos 
      if(millis()-time > 3000){//Caso a variável time despareada seja 3 segundos menor que a função millis, o if é verdadeiro.
      escolhido = true;} 
      
    }

    if(escolhido == true){
    if(modoJogoIndex == 1){funcModoAprendizado();}
    else if(modoJogoIndex == 2){funcModoDesafioSolo();}
    else if(modoJogoIndex == 3){funcModoDesafioDupla();}  
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Escolha um modo:");
    lcd.setCursor(0,1); 
    lcd.print(modoJogo[modoJogoIndex]);
    lcd.setCursor(0,3);
    lcd.print(modoJogoIndex);



    modoJogoIndex++;

    if(modoJogoIndex >= sizeof(modoJogo)/sizeof(modoJogo[0])){//Reseta o loop de modos. "sizeof(modoJogo)/sizeof(modoJogo[0])" retorna o tamanho do array modoJogoIndex.
    modoJogoIndex = 0;
    }
    
  }
}

void introducao(String modo){
  escolhido = false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Modo escolhido:");
  lcd.setCursor(0,1);
  lcd.print(modo);
  delay(2000);
} 

void funcModoAprendizado(){
  introducao("Aprendizado");

  funcPerguntas(perguntas);
  
  // Percorre todos os botões de resposta (1 a 8)
  while(true){
  for(int i = 1; i <= 8; i++) {
    if(digitalRead(Pin[i]) == 0) {  // Se qualquer botão for pressionado
      lcd.clear();
      lcd.setCursor(0,0);
      
      if(i == indiceAleatorio + 1) {  // Se for o botão correto
        lcd.print("Resposta correta!");
      } else {  // Se for qualquer outro botão
        lcd.print("Resposta incorreta!");
      }
      delay(1000); // Pequeno delay para evitar repetições indesejadas
      
    }

  }
  }

  funcModoAprendizado();
}

void funcModoDesafioSolo(){
  introducao("Desafio Solo");
}

void funcModoDesafioDupla(){
  introducao("Desafio Dupla");
}

void funcPerguntas(char *perguntas[]){
  Serial.println("Passando por FuncPerguntas");

  lcd.clear(); // Limpa o LCD antes de exibir a próxima pergunta
  
  lcd.setCursor(0, 0);
  lcd.print("Qual orgao:");

  do {
    indiceAleatorio = random(0, totalPerguntas); // Escolhe um índice aleatório
  } while (indiceAleatorio == ultimaPergunta); // Evita repetir a última pergunta

  ultimaPergunta = indiceAleatorio; // Atualiza a última pergunta exibida

  exibirNoLCD(perguntas[indiceAleatorio]); // Exibe a pergunta escolhida 
}

void exibirNoLCD(char *mensagem) {
  int i = 0, linha = 1;

  while (mensagem[i] != '\0' && linha < 4) { // Enquanto houver caracteres e linhas disponíveis
    lcd.setCursor(0, linha); // Move o cursor para a linha correta
    for (int j = 0; j < 20 && mensagem[i] != '\0'; j++, i++) {
    lcd.print(mensagem[i]); // Escreve caractere por caractere
    }
    linha++; // Vai para a próxima linha após 20 caracteres
    }
}

