# Projeto 40 Motores ESC - Sistema de Controle Massivo

O projeto de controle de 40 motores brushless foi pedido pelo cliente Em*** Be****. Ele é um sistema avançado de controle para até 40 motores brushless usando múltiplas placas PCA9685 e diferentes configurações de Arduino.

Todo o sistema teve que ser muito bem simulado, pois, o cliente iria montar o sistema em outro estado e as instruções tinham que ser claras para que ele pudesse seguir sem complicações.

Foi feito um estudo aprofundado sobre o uso de placas multiplexadoras e seus efeitos na divisão de corrente fornecida pelo arduino. Em teoria esse sistema funciona de forma direta com até 8 placas PCA9685 em paralelo com os terminai I2C do arduino. De forma indireta e utópica seria possível escalar esse sistema infinitamente visto que cada porta multiplexadora pode ser ligada a outra porta multiplexadora, podendo expandir até o endereço que a memória do arduino conseguisse armazenar. 

## Placa Alvo
- Arduino UNO (configurações de 1 e 3 Arduinos)

## Componentes Necessários
- 1-3 Arduino UNO
- 3 placas PCA9685 (PWM Servo Driver)
- 40 motores brushless
- 40 ESCs (Electronic Speed Controller)
- Potenciômetro 10kΩ
- Fonte de alimentação adequada para todos os motores
- Resistor pull-up 10kΩ (opcional)

## Bibliotecas Utilizadas
- `Wire.h` - Comunicação I2C
- `Adafruit_PWMServoDriver.h` - Controle do módulo PCA9685
- `Servo.h` - Controle direto de ESC (versão sem PCA9685)

## Implementações Disponíveis

### 🚀 Controle com 3 Placas PCA9685 (`Acionamento_3Placas_PCA9685/`)
Sistema escalável para controle de até 48 motores simultaneamente.

**Características:**
- **3 placas PCA9685** com endereços I2C únicos
- **48 canais PWM** (16 por placa)
- **Controle simultâneo** de todos os motores
- **Comunicação I2C** eficiente
- **Frequência 50Hz** otimizada para ESCs

**Endereços I2C:**
- **Placa 1**: 0x41 (A0 alterado)
- **Placa 2**: 0x42 (A1 alterado)  
- **Placa 3**: 0x43 (A0 e A1 alterados)

### ⚡ Controle com 1 Placa PCA9685 (`Acionamento_MotorBrushless_com_PCA9685/`)
Sistema básico para controle de até 16 motores.

**Características:**
- **1 placa PCA9685** (endereço padrão 0x40)
- **16 canais PWM** simultâneos
- **Controle direto** via potenciômetro
- **Monitoramento** via Serial

### 🔧 Controle Direto (`Acionamento_MotorBrushless_sem_PCA9685/`)
Controle simples de 1 motor via biblioteca Servo.

**Características:**
- **Controle direto** do ESC
- **Implementação simples**
- **Ideal para prototipagem**

## Conexões

### Sistema com 3 Placas PCA9685
- **PCA9685 SDA**: A4 (compartilhado)
- **PCA9685 SCL**: A5 (compartilhado)
- **PCA9685 VCC**: 5V (compartilhado)
- **PCA9685 GND**: GND (compartilhado)
- **Potenciômetro**: Pino A0
- **ESCs**: Conectados aos canais 0-15 de cada placa

### Sistema com 1 Placa PCA9685
- **PCA9685 SDA**: A4
- **PCA9685 SCL**: A5
- **PCA9685 VCC**: 5V
- **PCA9685 GND**: GND
- **Potenciômetro**: Pino A2
- **ESCs**: Conectados aos canais 0-15

### Sistema Direto
- **ESC Signal**: Pino 6
- **ESC VCC**: Fonte de alimentação
- **ESC GND**: GND comum
- **Potenciômetro**: Pino A2

## Configurações Técnicas

### Sistema com 3 Placas
- **Frequência PWM**: 50Hz
- **Range de PWM**: 205-410 (mapeado de 0-1023)
- **Canais por placa**: 16
- **Total de canais**: 48
- **Atualização**: 50ms

### Sistema com 1 Placa
- **Frequência PWM**: 50Hz
- **Range de PWM**: 205-410
- **Canais**: 16
- **Atualização**: 20ms

### Sistema Direto
- **Range de Velocidade**: 0-179
- **Frequência**: Padrão Servo
- **Pino**: 6

## Funcionalidades

### Sistema de Controle Massivo
- **Controle Simultâneo**: Todos os motores controlados juntos
- **Sincronização**: Movimento coordenado de todos os motores
- **Escalabilidade**: Fácil expansão para mais motores
- **Eficiência**: Comunicação I2C otimizada

### Características Avançadas
- **Mapeamento Preciso**: Conversão analógica para PWM
- **Monitoramento**: Exibição de valores no Serial
- **Estabilidade**: Delays otimizados para evitar oscilações
- **Flexibilidade**: Controle individual ou em grupo

## Simulações Proteus

### Simulação com 1 Arduino
- **Arquivo**: `Projeto-40Motores-ESC_1Arduino [FINALIZADO].pdsprj`
- **Documentação**: `Folha_Simulação_Proteus_1Arduino.pdf`
- **Configuração**: Sistema básico com 1 Arduino

### Simulação com 3 Arduinos
- **Arquivo**: `Projeto-40Motores-ESC_3Arduinos [FINALIZADO].pdsprj`
- **Documentação**: `Folha_Simulação_Proteus_3Arduinos.pdf`
- **Configuração**: Sistema distribuído com 3 Arduinos

## Como Compilar

### Sistema com 3 Placas PCA9685
1. Abra `Acionamento_3Placas_PCA9685.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale as bibliotecas:
   - Wire (já incluída)
   - Adafruit_PWMServoDriver
4. Configure os endereços I2C das placas
5. Compile e faça upload

### Sistema com 1 Placa PCA9685
1. Abra `Acionamento_MotorBrushless_com_PCA9685.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale as bibliotecas necessárias
4. Compile e faça upload

### Sistema Direto
1. Abra `Acionamento_MotorBrushless_sem_PCA9685.ino` na IDE Arduino
2. Selecione a placa: Arduino UNO
3. Instale a biblioteca Servo
4. Compile e faça upload

## Código Principal

### Sistema com 3 Placas
```cpp
// Inicialização das placas
Adafruit_PWMServoDriver placa1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver placa2 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver placa3 = Adafruit_PWMServoDriver(0x43);

// Controle de todos os canais
for(int i=0; i<16; i++){
  placa1.setPWM(i, 0, valorPWM);
  placa2.setPWM(i, 0, valorPWM);
  placa3.setPWM(i, 0, valorPWM);
}
```

## Configuração de Endereços I2C

### Placas PCA9685
- **Placa 1**: Conecte A0 ao VCC, deixe A1 em GND
- **Placa 2**: Conecte A1 ao VCC, deixe A0 em GND
- **Placa 3**: Conecte A0 e A1 ao VCC

### Verificação de Endereços
Use um scanner I2C para verificar se os endereços estão corretos:
```cpp
#include <Wire.h>
void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Scanner I2C");
}
```

## Aplicações

### Projetos Industriais
- **Sistemas de Conveyor**: Controle de esteiras industriais
- **Robótica Industrial**: Manipuladores com múltiplos motores
- **Automação**: Sistemas de produção automatizados

### Projetos Educacionais
- **Demonstração de Escalabilidade**: Controle de múltiplos motores
- **Aprendizado I2C**: Comunicação entre dispositivos
- **Projetos de Robótica**: Sistemas complexos

### Aplicações Específicas
- **Drones Multirrotor**: Controle de múltiplos motores
- **Carros RC**: Sistemas de tração múltipla
- **Ventilação Industrial**: Controle de múltiplos ventiladores

## Segurança

### Precauções Importantes
- **Fonte Adequada**: Use fonte capaz de alimentar todos os motores
- **Fusíveis**: Instale fusíveis apropriados para cada grupo de motores
- **Ventilação**: Mantenha ESCs bem ventilados
- **Calibração**: Calibre todos os ESCs antes do uso
- **Teste Gradual**: Teste com poucos motores primeiro

### Limitações
- **Corrente Total**: Verifique capacidade da fonte
- **Temperatura**: Monitore aquecimento dos ESCs
- **Comunicação I2C**: Limite de dispositivos no barramento
- **Latência**: Considerar delays de comunicação

## Troubleshooting

### Problemas Comuns
- **Motores não respondem**: Verifique endereços I2C
- **Comunicação I2C**: Verifique conexões SDA/SCL
- **Fonte insuficiente**: Verifique capacidade de corrente
- **Aquecimento**: Reduza número de motores ativos

### Soluções
- **Scanner I2C**: Use para verificar endereços
- **Teste Individual**: Teste cada placa separadamente
- **Monitoramento**: Use Serial para debug
- **Refrigeração**: Melhore ventilação dos ESCs

## Manutenção

- Verificar conexões I2C regularmente
- Monitorar temperatura dos ESCs
- Testar funcionamento de cada placa
- Verificar fonte de alimentação
- Calibrar ESCs periodicamente
- Limpar conexões se necessário

## Documentação Adicional

- **Imagens**: Fotos do projeto montado
- **Diagramas**: Circuitos de conexão
- **Simulações**: Arquivos Proteus para teste
- **GIFs**: Demonstrações visuais do funcionamento
