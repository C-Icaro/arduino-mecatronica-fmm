# Projeto CarWash - Sistema Automatizado de Lavagem

O projeto CarWash foi desenvolvido para obtenção de nota final na matéria de Circuitos Integrados e envolvia código + protótipo físico. Ele se propõe a ser um sistema automatizado de lavagem de veículos com controle de esteira e múltiplos estágios de limpeza.

## Placa Alvo
- ESP32

## Componentes Necessários
- ESP32 Dev Module
- 4 motores de lavagem (M1, M2, M3, M4)
- Motor da esteira
- 5 sensores de posição (S1-S5)
- Botão de emergência
- Botão de inicialização
- LED verde (espera)
- LED vermelho (emergência)
- Circuito integrado de controle (versão CI)

## Implementações Disponíveis

### 🔧 Versão Microcontrolada (`Projeto_CarWash_MicroControlado/`)
Controle direto via ESP32 com sequência programada.

**Características:**
- Sequência fixa de lavagem
- Controle temporal dos motores
- Sistema de emergência integrado
- Orquestração automática dos estágios

### ⚡ Versão Circuito Integrado (`Projeto_CarWash_CircuitoIntegrado/`)
Controle baseado em sensores com circuito integrado.

**Características:**
- Controle baseado em sensores
- Ativação sequencial por posição
- Sistema de emergência via CI
- Controle mais preciso de posicionamento

## Conexões - Versão Microcontrolada

### Sensores
- **S1**: Pino 34
- **S2**: Pino 35  
- **S3**: Pino 32
- **S4**: Pino 33
- **S5**: Pino 25

### Motores
- **M1**: Pino 26
- **M2**: Pino 27
- **M3**: Pino 14
- **M4**: Pino 12
- **Esteira**: Pino 13

### Controles
- **Botão Inicialização**: Pino 36 (INPUT_PULLUP)
- **Botão Emergência**: Pino 39 (via CI)

### LEDs
- **LED Verde (Espera)**: Pino 22
- **LED Vermelho (Emergência)**: Pino 23

## Conexões - Versão Circuito Integrado

### Sensores
- **S1**: Pino 34
- **S2**: Pino 35
- **S3**: Pino 32
- **S4**: Pino 33
- **S5**: Pino 25

### Motores
- **M1**: Pino 26
- **M2**: Pino 27
- **M3**: Pino 14
- **M4**: Pino 12
- **Esteira**: Pino 13

### Controles
- **Botão Inicialização**: Pino 15 (INPUT_PULLUP)
- **Botão Emergência**: Pino 2 (via CI)

### LEDs
- **LED Verde (Espera)**: Pino 11
- **LED Vermelho (Emergência)**: Pino 12

## Funcionalidades

### Sistema de Lavagem
1. **Inicialização**: Botão para iniciar o processo
2. **Transporte**: Esteira move o veículo através dos estágios
3. **Lavagem Sequencial**: 4 estágios de limpeza (M1-M4)
4. **Finalização**: Veículo sai do sistema

### Sistema de Emergência
- **Botão de Emergência**: Para todo o processo imediatamente
- **LED Vermelho**: Indica estado de emergência
- **Evacuação**: Move veículo para fora do sistema
- **Reset**: Retorna ao estado inicial após emergência

### Indicadores Visuais
- **LED Verde**: Sistema em espera/standby
- **LED Vermelho**: Estado de emergência ativo

## Sequência de Operação

### Versão Microcontrolada
1. Aguarda botão de inicialização
2. Liga esteira por 5 segundos
3. Ativa M1 por 3 segundos
4. Ativa M2 por 3 segundos  
5. Ativa M3 por 3 segundos
6. Ativa M4 por 3 segundos
7. Para esteira e finaliza

### Versão Circuito Integrado
1. Aguarda botão de inicialização
2. Liga esteira
3. Ativa motores conforme detecção dos sensores
4. Para quando sensor S5 é ativado
5. Sistema de emergência sempre ativo

## Como Compilar

### Versão Microcontrolada
1. Abra `Projeto_CarWash_MicroControlado.ino` na IDE Arduino
2. Selecione a placa: ESP32 Dev Module
3. Compile e faça upload

### Versão Circuito Integrado
1. Abra `Projeto_CarWash_CircuitoIntegrado.ino` na IDE Arduino
2. Selecione a placa: ESP32 Dev Module
3. Compile e faça upload

## Função Principal

```cpp
int func_motores(int esteira, int M1, int M2, int M3, int M4, int D)
```
- Controla todos os motores simultaneamente
- Parâmetro `D`: Tempo de delay em milissegundos
- Retorna 0 após execução

## Segurança

- **Sistema de Emergência**: Para imediatamente todos os motores
- **Evacuação Automática**: Move veículo para fora em emergência
- **Indicadores Visuais**: LEDs para status do sistema
- **Reset Automático**: Retorna ao estado inicial após emergência

## Aplicações

- Lavagem automática de veículos
- Sistemas industriais de limpeza
- Automação de processos sequenciais
- Projetos educacionais de automação

## Manutenção

- Verificar conexões dos sensores regularmente
- Limpar sensores para detecção precisa
- Verificar funcionamento dos motores
- Testar sistema de emergência periodicamente
