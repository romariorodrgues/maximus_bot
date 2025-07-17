# Instruções de Montagem - Robô Maximus

## Preparação Inicial

### 1. Verificação dos Componentes
- [ ] Conferir todos os componentes da lista
- [ ] Testar Arduino Mega com sketch básico (Blink)
- [ ] Verificar voltagem das baterias
- [ ] Preparar ferramentas

### 2. Preparação do Chassi
- [ ] Cortar chassi em acrílico/MDF (dimensões: 30cm x 20cm)
- [ ] Fazer furos para fixação do Arduino (4 furos M3)
- [ ] Fazer furos para motores das lagartas (laterais)
- [ ] Fazer furo para chave liga/desliga
- [ ] Furos para sensores ultrassônicos (frente e lateral)
- [ ] Lixar e limpar o chassi

## Montagem Mecânica

### 3. Instalação dos Motores e Lagartas
```
Passo a passo:
1. Fixar motores DC nas laterais do chassi
2. Alinhar eixos dos motores com furos das rodas das lagartas
3. Montar sistema de lagartas/esteiras
4. Testar movimento livre das lagartas
5. Verificar alinhamento e tensão adequada
```

### 4. Montagem da Estrutura dos Braços
```
Materiais: Suportes de servo, parafusos M3, servos SG90
1. Fixar servo da cabeça na parte frontal superior
2. Criar braços usando suportes de servo
3. Posicionar servos dos braços nas laterais
4. Testar movimento completo dos servos
```

### 5. Instalação dos Sensores
```
Sensores Ultrassônicos:
- Sensor frontal: Altura 15cm do solo, virado para frente
- Sensor lateral: Altura 10cm do solo, virado 45° à direita
- Fixar com parafusos ou cola quente
- Deixar cabos longos para conexão
```

## Montagem Eletrônica

### 6. Preparação da Alimentação
```
Circuito de Alimentação:
Bateria 7.4V → Regulador LM2596 → 5V para Arduino
                ↓
            Motores DC (via L298N)

Bateria 9V → Arduino VIN (backup)
```

### 7. Conexões do Arduino Mega

#### Conexões dos Motores (L298N)
```
Arduino → L298N
Pino 2  → IN1 (Motor Esquerdo Forward)
Pino 3  → IN2 (Motor Esquerdo Backward)
Pino 4  → ENA (Motor Esquerdo PWM)
Pino 5  → IN3 (Motor Direito Forward)
Pino 6  → IN4 (Motor Direito Backward)
Pino 7  → ENB (Motor Direito PWM)

Alimentação L298N:
+12V da bateria LiPo
GND comum
+5V do Arduino para lógica
```

#### Conexões dos Sensores Ultrassônicos
```
Arduino → HC-SR04 Frontal
Pino 8  → Trig
Pino 9  → Echo
+5V    → VCC
GND    → GND

Arduino → HC-SR04 Lateral
Pino 10 → Trig
Pino 11 → Echo
+5V    → VCC
GND    → GND
```

#### Conexões dos Servo Motores
```
Arduino → Servos
Pino 12 → Servo Cabeça (sinal)
Pino 13 → Servo Braço Esquerdo (sinal)
Pino 14 → Servo Braço Direito (sinal)
+5V    → VCC (todos os servos)
GND    → GND (todos os servos)
```

#### Conexões do Display LCD
```
Arduino → LCD 16x2
Pino 22 → RS
Pino 23 → Enable
Pino 24 → D4
Pino 25 → D5
Pino 26 → D6
Pino 27 → D7
+5V    → VDD
GND    → VSS
Potenciômetro 10kΩ → V0 (contraste)
```

#### Conexões do Bluetooth HC-05
```
Arduino → HC-05
Pino 18 → RX
Pino 19 → TX
+5V    → VCC
GND    → GND
```

### 8. Diagrama de Conexões Detalhado

```
                    ARDUINO MEGA 2560
                    ┌─────────────────┐
                    │  ┌─┐ ┌─┐ ┌─┐   │
         +5V ───────┤  │ │ │ │ │ │   │
         GND ───────┤  └─┘ └─┘ └─┘   │
                    │                │
    Motor L  ───────┤  2  3  4       │
    Motor R  ───────┤  5  6  7       │
    US Front ───────┤  8  9          │
    US Side  ───────┤ 10 11          │
    Servos   ───────┤ 12 13 14       │
    Status   ───────┤ 13             │
    BT HC-05 ───────┤ 18 19          │
    LCD      ───────┤ 22→27          │
                    └─────────────────┘
```

## Programação e Configuração

### 9. Upload do Código
```
1. Conectar Arduino ao computador via USB
2. Abrir Arduino IDE
3. Selecionar placa: Arduino Mega 2560
4. Selecionar porta COM correta
5. Fazer upload do código maximus_robot.ino
6. Verificar mensagens no Serial Monitor
```

### 10. Calibração dos Servos
```
Posições de Calibração:
- Cabeça: 90° (centro) = olhando para frente
- Braço Esquerdo: 90° = posição neutra
- Braço Direito: 90° = posição neutra

Ajustar no código se necessário:
- Modificar valores iniciais se servos não estão alinhados
- Testar limites mínimos e máximos de movimento
```

### 11. Teste dos Sensores
```
1. Verificar leituras dos sensores ultrassônicos
2. Testar detecção de obstáculos
3. Calibrar distância mínima de segurança
4. Verificar ângulos de detecção
```

## Configuração do Controle Remoto

### 12. Configuração do Bluetooth
```
1. Parear HC-05 com smartphone
   - Nome: HC-05 ou similar
   - PIN: 1234 ou 0000
2. Instalar app de controle Bluetooth
   - Serial Bluetooth Terminal
   - Arduino Bluetooth Controller
3. Testar comandos básicos:
   F = Frente, B = Trás, L = Esquerda, R = Direita, S = Parar
```

### 13. App Recomendado (Android)
```
Nome: "Serial Bluetooth Terminal"
Configuração de Botões:
┌─────┬─────┬─────┐
│  H  │  F  │  U  │  H=Cabeça, F=Frente, U=Braços cima
├─────┼─────┼─────┤
│  L  │  S  │  R  │  L=Esquerda, S=Parar, R=Direita
├─────┼─────┼─────┤
│  A  │  B  │  D  │  A=Auto, B=Trás, D=Braços baixo
└─────┴─────┴─────┘
```

## Testes Finais

### 14. Checklist de Testes
- [ ] Teste de movimento para frente/trás
- [ ] Teste de curvas esquerda/direita
- [ ] Teste de detecção de obstáculos
- [ ] Teste de modo autônomo
- [ ] Teste de controle remoto Bluetooth
- [ ] Teste de movimento da cabeça
- [ ] Teste de movimento dos braços
- [ ] Teste de display dos olhos
- [ ] Teste de duração da bateria

### 15. Troubleshooting Comum

| Problema | Possível Causa | Solução |
|----------|----------------|---------|
| Motores não funcionam | Bateria fraca ou conexões | Verificar tensão e cabos |
| Servo treme | Alimentação insuficiente | Usar fonte externa para servos |
| Sensor não detecta | Cabos soltos | Verificar conexões Trig/Echo |
| Bluetooth não conecta | Pareamento incorreto | Resetar HC-05 e parear novamente |
| Display não funciona | Contraste ou conexões | Ajustar potenciômetro e cabos |

## Melhorias Futuras
1. **Camera FPV**: Adicionar módulo de câmera
2. **Sensor de Linha**: Para seguir trajetos
3. **Braço Mecânico**: Garra funcional
4. **Sensor de Som**: Detecção de comandos de voz
5. **LEDs RGB**: Olhos mais expressivos
6. **GPS**: Navegação autônoma
7. **IA**: Reconhecimento de objetos

## Segurança
⚠️ **ATENÇÃO**:
- Sempre desligar antes de fazer conexões
- Verificar polaridade das baterias
- Não curto-circuitar alimentação
- Usar óculos de proteção ao cortar/furar
- Manter ferro de solda longe de materiais inflamáveis
- Supervisionar crianças durante a montagem
