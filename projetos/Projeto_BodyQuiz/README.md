# Projeto BodyQuiz - Jogo Educativo de Anatomia Humana

O projeto Body Quiz foi um projeto solicitado por cliente. Ele é um jogo interativo educativo sobre anatomia humana desenvolvido para Arduino, com múltiplos modos de jogo e interface LCD.

## Placa Alvo
- Arduino UNO

## Componentes Necessários
- Arduino UNO
- LCD I2C 16x4 (endereço 0x20)
- 9 botões (8 para órgãos + 1 controle)
- LED verde (resposta correta)
- LED vermelho (resposta incorreta)
- Buzzer para feedback sonoro
- Resistor pull-up 10kΩ (opcional)

## Bibliotecas Utilizadas
- `Wire.h` - Comunicação I2C
- `LiquidCrystal_I2C.h` - Controle do display LCD

## Implementações Disponíveis

### 🎯 Versão Completa (`bodyquiz_completo/`)
Sistema completo com 3 modos de jogo diferentes.

**Características:**
- **Modo Aprendizado**: Apresenta perguntas e respostas educativas
- **Modo Desafio Solo**: Jogo individual com pontuação
- **Modo Desafio Dupla**: Competição entre dois jogadores
- Sistema de perguntas aleatórias
- Seleção de modo via botão com delay

### 📚 Versão Aprendizado (`bodyquiz_aprendizado/`)
Foco exclusivo no modo educativo.

**Características:**
- Modo apenas de aprendizado
- Perguntas sobre órgãos humanos
- Feedback visual e sonoro
- Interface simplificada

### 🎮 Versão Básica (`bodyquiz_basico/`)
Implementação simplificada com modo único.

**Características:**
- Modo aprendizado único
- Interface básica
- Feedback com LEDs e buzzer
- Sistema de perguntas sequenciais

## Conexões

### Display LCD
- **SDA**: A4
- **SCL**: A5
- **VCC**: 5V
- **GND**: GND
- **Endereço I2C**: 0x20

### Botões (Versão Completa)
- **Botão Controle**: Pino 2
- **Órgão 1**: Pino 3
- **Órgão 2**: Pino 4
- **Órgão 3**: Pino 5
- **Órgão 4**: Pino 6
- **Órgão 5**: Pino 7
- **Órgão 6**: Pino 8
- **Órgão 7**: Pino 9
- **Órgão 8**: Pino 10

### Botões (Versões Básica e Aprendizado)
- **Botão Controle**: Pino 2
- **Órgão 1**: Pino 3
- **Órgão 2**: Pino 4
- **Órgão 3**: Pino 5
- **Órgão 4**: Pino 6
- **Órgão 5**: Pino 7
- **Órgão 6**: Pino 8
- **Órgão 7**: Pino 9
- **Órgão 8**: Pino 10

### LEDs e Buzzer
- **LED Verde**: Pino A1
- **LED Vermelho**: Pino A0
- **Buzzer**: Pino A2

## Banco de Perguntas

### Órgãos e Funções
1. **Coração** - "Bombeia sangue para o corpo?"
2. **Pulmões** - "Troca de oxigênio por CO2?"
3. **Baço** - "Filtra sangue e armazena células sanguíneas?"
4. **Fígado** - "Produz bile e desintoxica?"
5. **Estômago** - "Digere alimentos com ácidos?"
6. **Rins** - "Filtra sangue e produz urina?"
7. **Intestinos** - "Absorve nutrientes dos alimentos?"
8. **Pâncreas** - "Produz insulina e regula açúcar?"

## Funcionalidades

### Sistema de Jogo
- **Perguntas Aleatórias**: Evita repetição consecutiva
- **Feedback Imediato**: LEDs e buzzer para respostas
- **Interface Intuitiva**: Display LCD com instruções claras
- **Múltiplos Modos**: Diferentes experiências de aprendizado

### Modos de Jogo (Versão Completa)
1. **Aprendizado**: Modo educativo sem pontuação
2. **Desafio Solo**: Jogo individual com pontuação
3. **Desafio Dupla**: Competição entre dois jogadores

### Sistema de Controle
- **Seleção de Modo**: Botão com delay de 3 segundos
- **Navegação**: Botões para cada órgão
- **Feedback**: LEDs coloridos e buzzer

## Como Compilar

### Versão Completa
1. Abra `Codigo-Prog-ProjetoBodyQuiz.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale as bibliotecas Wire e LiquidCrystal_I2C
4. Compile e faça upload

### Versão Aprendizado
1. Abra `Codigo02_BodyQuiz-SomenteAprendizado.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale as bibliotecas necessárias
4. Compile e faça upload

### Versão Básica
1. Abra `Codigo02-BodyQuiz.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale as bibliotecas necessárias
4. Compile e faça upload

## Estrutura do Código

### Arrays Principais
```cpp
char *perguntas[] = {
  "Bombeia sangue para o corpo?",
  "Troca de oxigenio por CO2?",
  // ... mais perguntas
};

char *respostas[] = {
  "Coracao",
  "Pulmoes", 
  // ... mais respostas
};
```

### Funções Principais
- `funcModoJogo()` - Seleção de modo
- `funcModoAprendizado()` - Modo educativo
- `funcModoDesafioSolo()` - Jogo individual
- `funcModoDesafioDupla()` - Competição

## Configurações

### Display LCD
- **Endereço I2C**: 0x20
- **Dimensões**: 16 colunas x 4 linhas
- **Backlight**: Ativado por padrão

### Botões
- **Pull-up**: Ativado internamente
- **Debounce**: Implementado via delay
- **Mapeamento**: Cada botão corresponde a um órgão

## Aplicações Educacionais

- **Ensino Fundamental**: Introdução à anatomia humana
- **Educação Médica**: Revisão de órgãos e funções
- **Projetos Escolares**: Demonstração prática de eletrônica
- **Aprendizado Interativo**: Combinação de hardware e software

## Melhorias Futuras

- Adicionar mais órgãos e sistemas
- Implementar sistema de pontuação persistente
- Adicionar modo cronometrado
- Incluir perguntas de múltipla escolha
- Sistema de níveis de dificuldade

## Manutenção

- Verificar conexões dos botões regularmente
- Limpar display LCD para melhor visibilidade
- Testar LEDs e buzzer periodicamente
- Verificar funcionamento do I2C
- Calibrar sensibilidade dos botões
