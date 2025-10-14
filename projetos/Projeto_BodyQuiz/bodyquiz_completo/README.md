# BodyQuiz Completo

Jogo educativo sobre anatomia humana com múltiplos modos de jogo.

## Placa Alvo
- Arduino UNO

## Componentes Necessários
- LCD I2C 16x4 (endereço 0x20)
- 9 botões conectados aos pinos 2-10
- LEDs para feedback
- Buzzer para sons

## Bibliotecas Utilizadas
- `Wire.h` - Comunicação I2C
- `LiquidCrystal_I2C.h` - Controle do display LCD

## Funcionalidades
- **Modo Aprendizado**: Apresenta perguntas e respostas educativas
- **Modo Desafio Solo**: Jogo individual com pontuação
- **Modo Desafio Dupla**: Competição entre dois jogadores
- Sistema de perguntas aleatórias sobre órgãos humanos
- Feedback visual e sonoro

## Conexões
- LCD I2C: SDA (A4), SCL (A5), VCC (5V), GND
- Botões: Pinos 2-10 com pull-up interno
- LEDs e buzzer: Conforme definido no código

## Como Compilar
1. Abra o arquivo `Codigo-Prog-ProjetoBodyQuiz.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale as bibliotecas necessárias
4. Compile e faça upload

## Estrutura do Código
- Array de perguntas sobre órgãos humanos
- Array de respostas correspondentes
- Sistema de seleção de modo via botões
- Lógica de jogo com pontuação e feedback
