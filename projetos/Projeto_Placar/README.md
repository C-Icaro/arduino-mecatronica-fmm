# Projeto Placar - Sistema de Displays HT16K33

O projeto placar foi uma iniciativa para produzir um placar barato e multifuncional para as quadras da Fundação Mathias Machline. O sistema de placar eletrônico foi feito utilizando múltiplos displays HT16K33 com diferentes configurações e simulações Proteus.

Os displays de 16 segmentos foram escolhidos por sua completude na exibição de todo o alfabeto e versatilidade para múltiplos formatos, o display de 7 segmentos foi descartado por ser simples demais para a aplicação e o display de 14 segmentos foi desconsiderado pela falta de material complementar e dificuldade de compra, pois, visto que é um meio termo, não tem tanta capilaridade. No entanto, para a utilziar os aproximadamente 36 displays de 16 segmentos em um só arduino foi necessário utilizar o multiplexador HT16k33 adaptado.

Foi feito um longo estudo acerca do multiplexador HT16k33 para compreender sua correta utilização com os displays e como manipular e mapear seus endereços lógicos. Por semanas o problema era que todas as placas estavam lendo o mesmo sinal. Isso me levou a acreditar que o problema estava no simulador e que não havia como progredir sem o multiplexador em mãos. No entanto, certa noite quando tentei novamente encontrei uma forma de manipular o endereço do dispotivo em simulação. Segue abaixo:

<div align="center">
  Figura 01: Diagrama elétrico com endereço variável.
</div>
<div align="center">
  <img src="Teste03 - Diagrama elétrico Final 01.jpg" width="800">
</div>
<div align="center">
  Fonte: Carlos Icaro, 2024.
</div>

Obs: Os arquivos binário (.hex ou .elf ) de código compilado foram perdidos. É necessário recompilar o código em binário caso queira fazer a simulação no Proteus 8.6.

O projeto não foi concluído. Ainda é necessário finalizar o diagrama, o firmware e a interface web para manipulação do sistema.



## Placa Alvo
- Arduino UNO

## Componentes Necessários
- Arduino UNO
- 1-6 módulos HT16K33 (multiplexador para display de 7 e 16 segmentos)
- Resistor pull-up 10kΩ
- Fonte de alimentação 5V
- Jumpers para conexões I2C

## Bibliotecas Utilizadas
- `Wire.h` - Comunicação I2C
- `HT16K33Disp.h` - Biblioteca para displays HT16K33
- `HT16K33.h` - Biblioteca alternativa HT16K33

## Implementações Disponíveis

### 🎮 Teste Básico (`teste_ht16k33_basico.ino`)
Teste simples com um único display HT16K33.

**Características:**
- **1 display HT16K33** (endereço 0x70)
- **Exibição alternada** "GAME" e "OVER"
- **Delay de 1 segundo** entre mudanças
- **Implementação simples** para teste inicial

### 🏆 Múltiplos Displays (`Multiplos_Displays_Teste.ino`)
Sistema com 6 displays HT16K33 simultâneos.

**Características:**
- **6 displays HT16K33** com endereços únicos
- **Endereços I2C**: 0x70, 0x71, 0x72, 0x73, 0x74, 0x75
- **Exibição simultânea** de diferentes textos
- **Controle individual** de cada display

## Configurações de Hardware

### Endereços I2C dos Displays
```cpp
int um = 0x70;      // Display 1
int dois = 0x71;    // Display 2
int tres = 0x72;    // Display 3
int quatro = 0x73;  // Display 4
int cinco = 0x74;   // Display 5
int seis = 0x75;    // Display 6
```

### Conexões I2C
- **SDA**: Pino A4 (compartilhado)
- **SCL**: Pino A5 (compartilhado)
- **VCC**: 5V (compartilhado)
- **GND**: GND (compartilhado)

## Simulações Proteus

### Circuito Básico (`Circuito Proteus/`)
- **Arquivo**: `Teste HT16K33.pdsprj`
- **Configuração**: Display único
- **Teste**: Funcionamento básico

### Múltiplos Displays (`Circuito Proteus - Multiplos/`)
- **Arquivo**: `Teste HT16K33.pdsprj`
- **Configuração**: 6 displays em paralelo
- **Teste**: Controle simultâneo

### Teste 2 Módulos (`Circuito Proteus - Teste 2 modulos/`)
- **Arquivo**: `Teste HT16K33.pdsprj`
- **Configuração**: 2 displays
- **Teste**: Comunicação I2C

### Display Único (`Circuito Proteus - Unico/`)
- **Arquivo**: `Teste HT16K33.pdsprj`
- **Configuração**: 1 display
- **Teste**: Funcionamento individual

## Funcionalidades

### Sistema de Exibição
- **Texto**: Exibição de strings nos displays
- **Números**: Exibição de valores numéricos
- **Controle de Brilho**: Ajuste de intensidade
- **Limpeza**: Clear dos displays
- **Inicialização**: Setup automático

### Características Técnicas
- **Comunicação I2C**: Protocolo eficiente
- **Endereçamento**: Múltiplos dispositivos
- **Resolução**: 4 dígitos por display
- **Caracteres**: Suporte a alfanuméricos
- **Brilho**: 16 níveis ajustáveis

## Código Principal

### Teste Básico
```cpp
#include <HT16K33Disp.h>
HT16K33Disp dsp;
int add = 0x70;

void setup() {
  dsp.Init(add, 8);
  dsp.Clear(add);
}

void loop() {
  dsp.Text(add, "GAME");
  delay(1000);
  dsp.Text(add, "OVER");
  delay(1000);
}
```

### Múltiplos Displays
```cpp
#include <HT16K33Disp.h>
HT16K33Disp dsp;

int um = 0x70, dois = 0x71, tres = 0x72;
int quatro = 0x73, cinco = 0x74, seis = 0x75;

void setup() {
  dsp.Init(um, 8); dsp.Clear(um);
  dsp.Init(dois, 8); dsp.Clear(dois);
  // ... inicialização dos outros displays
}

void loop() {
  dsp.Text(um, "Um");
  dsp.Text(dois, "Dois");
  dsp.Text(tres, "Tres");
  // ... exibição nos outros displays
}
```

## Configuração de Endereços I2C

### Jumpers dos Displays
- **Display 1**: Sem jumpers (0x70)
- **Display 2**: A0 conectado (0x71)
- **Display 3**: A1 conectado (0x72)
- **Display 4**: A0 e A1 conectados (0x73)
- **Display 5**: A2 conectado (0x74)
- **Display 6**: A0 e A2 conectados (0x75)

### Verificação de Endereços
```cpp
#include <Wire.h>
void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Scanner I2C");
}
```

## Como Compilar

### Teste Básico
1. Abra `teste_ht16k33_basico.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale a biblioteca HT16K33Disp
4. Compile e faça upload

### Múltiplos Displays
1. Abra `Multiplos_Displays_Teste.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale a biblioteca HT16K33Disp
4. Configure os endereços I2C
5. Compile e faça upload

## Modelagem 3D

### Carcaça (`Modelagem/Carcaça.par`)
- **Arquivo**: Modelo 3D da carcaça
- **Formato**: PAR (SolidWorks)
- **Função**: Proteção e montagem dos displays

## Aplicações

### Esportes
- **Placares de Futebol**: Controle de gols e tempo
- **Basquete**: Pontuação e cronômetro
- **Vôlei**: Sets e pontos
- **Tênis**: Games e sets

### Indústria
- **Contadores**: Produção e peças
- **Medidores**: Temperatura e pressão
- **Sistemas de Controle**: Status e alertas

### Educacional
- **Demonstrações**: Controle de displays
- **Projetos**: Sistemas de informação
- **Aprendizado**: Comunicação I2C

## Funcionalidades Avançadas

### Biblioteca HT16K33
- **displayInt()**: Exibição de números inteiros
- **displayFloat()**: Exibição de números decimais
- **setBrightness()**: Controle de brilho
- **setBlink()**: Efeito de piscar
- **displayClear()**: Limpeza do display

### Controle de Brilho
```cpp
seg.setBrightness(2);  // Brilho nível 2 (0-15)
```

### Efeitos Visuais
```cpp
seg.setBlink(1);        // Piscar ativado
seg.displayClear();     // Limpar display
```

## Troubleshooting

### Problemas Comuns
- **Display não funciona**: Verificar endereço I2C
- **Comunicação I2C**: Verificar conexões SDA/SCL
- **Texto não aparece**: Verificar inicialização
- **Múltiplos displays**: Verificar endereços únicos

### Soluções
- **Scanner I2C**: Use para verificar endereços
- **Teste Individual**: Teste cada display separadamente
- **Verificar Jumpers**: Confirme configuração de endereços
- **Monitor Serial**: Use para debug

## Manutenção

- Verificar conexões I2C regularmente
- Limpar displays para melhor visibilidade
- Testar funcionamento de cada módulo
- Verificar fonte de alimentação
- Calibrar brilho conforme necessário

## Documentação Adicional

- **Imagens**: Fotos dos testes realizados
- **Simulações**: Arquivos Proteus para teste virtual
- **Modelagem**: Arquivo 3D da carcaça
- **Código**: Código fonte e bibliotecas utilizadas
