# Teste Múltiplos Displays HT16K33

Controle de múltiplos displays HT16K33 simultaneamente.

## Placa Alvo
- Arduino UNO

## Componentes Necessários
- 6 displays HT16K33 (endereços 0x70-0x75)
- Resistor pull-up 10kΩ

## Bibliotecas Utilizadas
- `HT16K33Disp.h` - Biblioteca para display HT16K33

## Funcionalidades
- Controle de até 6 displays simultaneamente
- Exibição de texto em todos os displays
- Endereçamento I2C individual
- Sincronização de conteúdo

## Conexões
- Todos os displays compartilham SDA (A4) e SCL (A5)
- Cada display tem endereço I2C único (0x70-0x75)
- VCC: 5V, GND: GND

## Endereços I2C
- Display 1: 0x70
- Display 2: 0x71
- Display 3: 0x72
- Display 4: 0x73
- Display 5: 0x74
- Display 6: 0x75

## Como Compilar
1. Abra o arquivo `Multiplos_Displays_Teste.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale a biblioteca HT16K33Disp
4. Compile e faça upload

## Configuração de Endereços
- Configure os jumpers nos displays para endereços únicos
- Verifique a comunicação I2C com scanner se necessário
- Teste individualmente cada display antes da montagem final
