const int micPin = 25; // Microfone conectado ao pino A0
const int threshold = 600; // Ajuste este valor com base nos seus testes

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial a 115200 baud
}

void loop() {
  int micValue = analogRead(micPin); // Lê o valor analógico do microfone

  if (micValue > threshold) {
    Serial.println("Palma detectada!"); // Exibe mensagem quando uma palma é detectada
    delay(300); // Pequeno atraso para evitar múltiplas detecções da mesma palma
  }

  delay(10); // Pequeno atraso para tornar a saída mais legível


}
763 749 778 716 719 734 720

ligar 
783 800 790 726 735 779 731 762 767