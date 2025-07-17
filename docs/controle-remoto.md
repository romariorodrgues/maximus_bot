# 📱 Guia de Controle Remoto - Robô Maximus

## Configuração do Bluetooth

### 1. Pareamento Inicial
1. Ligue o robô Maximus
2. No smartphone, vá em **Configurações > Bluetooth**
3. Procure por **"HC-05"** ou **"Maximus"**
4. Conecte usando PIN: **1234** ou **0000**

### 2. Apps Recomendados

#### Android
- **Serial Bluetooth Terminal** (Gratuito)
- **Arduino Bluetooth Controller** (Gratuito)
- **Bluetooth Terminal HC-05** (Gratuito)

#### iOS
- **LightBlue Explorer** (Gratuito)
- **Serial Bluetooth Terminal** (Pago)

## 🎮 Comandos de Controle

### Movimentação Básica
| Tecla | Comando | Ação |
|-------|---------|------|
| `F` | Forward | 🚗 Mover para frente |
| `B` | Backward | ⬅️ Mover para trás |
| `L` | Left | ⬅️ Virar à esquerda |
| `R` | Right | ➡️ Virar à direita |
| `S` | Stop | ⏹️ Parar motores |

### Modos de Operação
| Tecla | Comando | Ação |
|-------|---------|------|
| `A` | Autonomous | 🤖 Ativar modo autônomo |
| `M` | Manual | 🎮 Ativar controle manual |

### Movimentos dos Servos
| Tecla | Comando | Ação |
|-------|---------|------|
| `H` | Head | 🎭 Mover cabeça aleatoriamente |
| `U` | Up | 🙌 Levantar braços |
| `D` | Down | 👇 Abaixar braços |

### Controle de Velocidade
| Tecla | Comando | Ação |
|-------|---------|------|
| `+` | Speed Up | ⚡ Aumentar velocidade |
| `-` | Speed Down | 🐌 Diminuir velocidade |

## 📱 Configuração do App Serial Bluetooth Terminal

### Layout de Botões Recomendado

```
┌─────────────────────────────────┐
│        ROBÔ MAXIMUS             │
├─────┬─────┬─────┬─────┬─────────┤
│  H  │  F  │  U  │  +  │   A     │
│Head │Fren │Arms │Fast │ Auto    │
├─────┼─────┼─────┼─────┼─────────┤
│  L  │  S  │  R  │  -  │   M     │
│Left │Stop │Right│Slow │Manual   │
├─────┼─────┼─────┼─────┼─────────┤
│     │  B  │  D  │     │   S     │
│     │Back │Arms │     │ Stop    │
└─────┴─────┴─────┴─────┴─────────┘
```

### Configuração de Macros

#### Macro 1: "Cumprimentar"
```
Sequência: H+U+delay(1000)+D+S
Descrição: Mover cabeça, levantar braços, pausar, abaixar braços, parar
```

#### Macro 2: "Exploração"
```
Sequência: A+F
Descrição: Ativar modo autônomo e começar a mover
```

#### Macro 3: "Parada de Emergência"
```
Sequência: S+M
Descrição: Parar motores e mudar para modo manual
```

## 🔊 Comandos de Voz (Futuro)

### Comandos Planejados
- "Maximus, frente"
- "Maximus, parar"
- "Maximus, olhar ao redor"
- "Maximus, acenar"
- "Maximus, modo autônomo"

## 📊 Interface de Status

### Informações no Display
```
┌─────────────────┐
│   👁️      👁️   │  <- Olhos expressivos
│ AUTO D:25cm V:75%│  <- Status atual
└─────────────────┘
```

**Legenda:**
- **AUTO/MAN**: Modo atual (Autônomo/Manual)
- **D:XXcm**: Distância do obstáculo mais próximo
- **V:XX%**: Velocidade atual dos motores

### Estados dos Olhos
- **👁️ 👁️**: Normal/Acordado
- **😊 😊**: Feliz (movimento suave)
- **😠 😠**: Alerta (obstáculo detectado)
- **😴 😴**: Dormindo (modo idle)
- **⚠️ ⚠️**: Emergência (bateria baixa/erro)

## 🛠️ Troubleshooting do Bluetooth

### Problemas Comuns

#### Não Consegue Conectar
1. Verificar se o módulo HC-05 está ligado (LED piscando)
2. Resetar pareamento: desparear e parear novamente
3. Verificar distância (máximo 10 metros)
4. Reiniciar Bluetooth do smartphone

#### Comandos Não Funcionam
1. Verificar se está conectado ao HC-05 correto
2. Verificar se app está enviando dados como texto
3. Testar com Serial Monitor no computador primeiro
4. Verificar se robô está ligado e funcionando

#### Conexão Instável
1. Verificar interferências (WiFi, outros Bluetooth)
2. Manter smartphone próximo ao robô
3. Verificar bateria do robô (baixa tensão afeta Bluetooth)
4. Reduzir taxa de envio de comandos

### Códigos de Erro (Via Serial)
```
E001: Sensor frontal não responde
E002: Sensor lateral não responde  
E003: Servo cabeça travado
E004: Motor esquerdo sem resposta
E005: Motor direito sem resposta
E006: Bateria baixa (<6V)
E007: Bluetooth desconectado
```

## 🔧 Configurações Avançadas

### Modificar Velocidades
```cpp
// No código Arduino, seção de configuração:
int motorSpeed = 150;        // Padrão (0-255)
int maxSpeed = 255;          // Velocidade máxima
int minSpeed = 50;           // Velocidade mínima
```

### Ajustar Sensibilidade dos Sensores
```cpp
const int SAFE_DISTANCE = 20; // Distância mínima em cm
```

### Personalizar Movimentos da Cabeça
```cpp
// Movimento automático da cabeça a cada 2 segundos
const int HEAD_INTERVAL = 2000;
```

## 🎯 Dicas de Uso

### Modo Autônomo
- Funciona melhor em espaços abertos
- Evite superfícies muito reflexivas (vidro, espelhos)
- Mantenha área bem iluminada
- Retire obstáculos pequenos do chão

### Modo Manual
- Use velocidade baixa em espaços apertados
- Teste movimentos antes de usar velocidade máxima
- Mantenha contato visual com o robô
- Use comando "S" (Stop) para emergências

### Conservação da Bateria
- Use modo manual quando possível (menor consumo)
- Evite velocidades máximas constantemente
- Desligue quando não usar por mais de 30 minutos
- Monitore voltagem da bateria no display

## 📈 Logs e Monitoramento

### Via Serial Monitor (9600 baud)
```
MAXIMUS V2.0 - Sistema Iniciado
Modo: AUTO | Bateria: 7.4V | Temp: 25°C
Sensores: F:25cm L:30cm | Motores: OK
Bluetooth: Conectado (Dispositivo: SM-G991B)
[15:30:25] Obstáculo detectado - Virando à esquerda
[15:30:27] Caminho livre - Continuando frente
[15:30:30] Comando recebido: 'H' - Movendo cabeça
```

### Arquivo de Log (Futuro)
- Histórico de movimentos
- Estatísticas de uso
- Eventos de erro
- Dados dos sensores ao longo do tempo
