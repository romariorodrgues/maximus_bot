# Esquemas Elétricos - Robô Maximus

## Diagrama Principal de Conexões

```
                            ROBÔ MAXIMUS - ESQUEMA ELÉTRICO
                                    
                    ┌─────────────────────────────────────┐
                    │          ARDUINO MEGA 2560          │
                    │                                     │
                    │   ┌─┐ ┌─┐ USB  ┌─┐ ┌─┐ ┌─┐ ┌─┐   │
                    │   │ │ │ │  ■   │ │ │ │ │ │ │ │   │
                    │   └─┘ └─┘       └─┘ └─┘ └─┘ └─┘   │
                    │                                     │
    MOTOR ESQUERDO  │  2  3  4                           │
    MOTOR DIREITO   │  5  6  7                           │
    US FRONTAL      │  8  9                              │
    US LATERAL      │ 10 11                              │
    SERVO CABEÇA    │ 12                                 │
    SERVO BRAÇO E   │ 13                                 │  
    SERVO BRAÇO D   │ 14                                 │
    LED STATUS      │ 13                                 │
    BLUETOOTH RX    │ 18                                 │
    BLUETOOTH TX    │ 19                                 │
    LCD RS          │ 22                                 │
    LCD EN          │ 23                                 │
    LCD D4-D7       │ 24 25 26 27                       │
                    │                                     │
                    │  VIN  5V  3V3  GND                 │
                    └──┬────┬───┬────┬──────────────────────┘
                       │    │   │    │
                       │    │   │    └─── GND COMUM
                       │    │   └────── +3.3V (reserva)
                       │    └────────── +5V LÓGICA
                       └─────────────── ENTRADA ALIMENTAÇÃO
                                       
```

## Sistema de Alimentação

```
    BATERIA LiPo 7.4V 2200mAh
             │
             ├─────────┐
             │         │
             │    ┌────▼────┐
             │    │ L298N   │
             │    │ MOTOR   │
             │    │ DRIVER  │
             │    └─────────┘
             │         │
             │    MOTORES DC
             │         
             │    ┌────▼────┐
             │    │ LM2596  │
             │    │REGULADOR│
             │    │ 7.4→5V  │
             │    └────┬────┘
             │         │
             └─────────┼─────── ARDUINO VIN
                       │
                  ┌────▼────┐
                  │ARDUINO  │
                  │  5V     │ ──── SENSORES + LCD + SERVOS
                  │  GND    │ 
                  └─────────┘
                  
    BATERIA 9V (BACKUP)
             │
             └─────────────── ARDUINO VIN (opcional)
```

## Conexões do Driver de Motor L298N

```
                    ┌─────────────────┐
                    │     L298N       │
                    │  MOTOR DRIVER   │
         ARDUINO ───┤                 │
           PIN 2 ───┤ IN1        OUT1 ├─── MOTOR ESQUERDO +
           PIN 3 ───┤ IN2        OUT2 ├─── MOTOR ESQUERDO -
           PIN 4 ───┤ ENA             │
           PIN 5 ───┤ IN3        OUT3 ├─── MOTOR DIREITO +
           PIN 6 ───┤ IN4        OUT4 ├─── MOTOR DIREITO -
           PIN 7 ───┤ ENB             │
                    │                 │
         +7.4V ─────┤ +12V            │
         +5V ───────┤ +5V             │
         GND ───────┤ GND             │
                    └─────────────────┘
```

## Conexões dos Sensores Ultrassônicos

```
    SENSOR FRONTAL HC-SR04          SENSOR LATERAL HC-SR04
    ┌─────────────────┐             ┌─────────────────┐
    │    [ ]   [ ]    │             │    [ ]   [ ]    │
    │   TRIG  ECHO    │             │   TRIG  ECHO    │
    └──┬───────┬──────┘             └──┬───────┬──────┘
       │       │                       │       │
    ┌──▼───────▼──┐                 ┌──▼───────▼──┐
    │ PIN8   PIN9 │                 │PIN10  PIN11 │
    │    ARDUINO  │                 │   ARDUINO   │
    │ +5V    GND  │                 │ +5V    GND  │
    └─────────────┘                 └─────────────┘
```

## Conexões dos Servo Motores

```
                    SERVOS SG90
                    
    SERVO CABEÇA           SERVO BRAÇO ESQ        SERVO BRAÇO DIR
    ┌─────────┐            ┌─────────┐            ┌─────────┐
    │  ┌─┐    │            │  ┌─┐    │            │  ┌─┐    │
    │  └─┘    │            │  └─┘    │            │  └─┘    │
    └─┬─┬─┬───┘            └─┬─┬─┬───┘            └─┬─┬─┬───┘
      │ │ │                  │ │ │                  │ │ │
      │ │ └──PIN12           │ │ └──PIN13           │ │ └──PIN14
      │ └────+5V             │ └────+5V             │ └────+5V
      └──────GND             └──────GND             └──────GND
```

## Display LCD 16x2

```
                    ┌─────────────────┐
                    │ [MAXIMUS ONLINE]│
                    │ [AUTO D:25cm   ]│
                    └─┬─┬─┬─┬─┬─┬─┬─┬─┘
                      │ │ │ │ │ │ │ │
    ARDUINO PIN ──────┘ │ │ │ │ │ │ └── PIN27 (D7)
    ARDUINO PIN ────────┘ │ │ │ │ └──── PIN26 (D6)
    ARDUINO PIN ──────────┘ │ │ └────── PIN25 (D5)  
    ARDUINO PIN ────────────┘ └──────── PIN24 (D4)
    ARDUINO PIN ──────────────────────── PIN23 (EN)
    ARDUINO PIN ──────────────────────── PIN22 (RS)
    
    +5V ──────────────────────────────── VDD
    GND ──────────────────────────────── VSS
    POTENCIÔMETRO 10kΩ ─────────────────── V0 (contraste)
```

## Módulo Bluetooth HC-05

```
                    ┌─────────────┐
                    │    HC-05    │
                    │ BLUETOOTH   │
                    │   MODULE    │
                    └─┬─┬─┬─┬─┬─┬─┘
                      │ │ │ │ │ │
    ARDUINO PIN18 ────┘ │ │ │ │ └── NC
    ARDUINO PIN19 ──────┘ │ │ └──── STATE
    +5V ───────────────────┘ └────── EN
    GND ─────────────────────────── GND
```

## Layout Físico do Robô (Vista Superior)

```
                    ┌─────────────────────────────┐
                    │          FRENTE             │
                    │                             │
                    │  [US]           [LCD]       │ ← Sensor + Display
                    │                             │
                    │ ┌───┐ ┌─────────────┐ ┌───┐ │
                    │ │ARM│ │   ARDUINO   │ │ARM│ │ ← Braços + Arduino
                    │ │ L │ │    MEGA     │ │ R │ │
                    │ └───┘ └─────────────┘ └───┘ │
                    │                             │
                    │  [BT]  [BATERIA]  [CHAVE]  │ ← Bluetooth + Energia
                    │                             │
              ┌─────┤ ████               ████ ├─────┐
              │MOTOR│ ████    [HEAD]    ████ │MOTOR│ ← Motores + Cabeça
              │  L  │ ████               ████ │  R  │   
              └─────┤ ████               ████ ├─────┘
                    │                             │
                    │ [US]                        │ ← Sensor Lateral
                    │                             │
                    └─────────────────────────────┘
                               TRÁS
```

## Diagrama de Estados do Sistema

```
                    ┌─────────────┐
                    │   INÍCIO    │
                    └──────┬──────┘
                           │
                    ┌──────▼──────┐
                    │INICIALIZAÇÃO│
                    │- Servos     │
                    │- Sensores   │
                    │- Display    │
                    └──────┬──────┘
                           │
                    ┌──────▼──────┐
                    │    IDLE     │ ◄─────────┐
                    │ Aguardando  │           │
                    │  Comando    │           │
                    └──┬───────┬──┘           │
                       │       │              │
              ┌────────▼──┐ ┌──▼────────┐     │
              │   MANUAL  │ │ AUTÔNOMO  │     │
              │  - Remote │ │ - Sensores│     │
              │  - Serial │ │ - Desvio  │     │
              └────────┬──┘ └──┬────────┘     │
                       │       │              │
                       └───────┼──────────────┘
                               │
                    ┌──────────▼──────────┐
                    │     EXECUÇÃO        │
                    │ - Mover Motores     │
                    │ - Atualizar Display │
                    │ - Mover Servos      │
                    └─────────────────────┘
```

## Lista de Sinais e Pinos

| Função | Pino Arduino | Componente | Tipo |
|--------|--------------|------------|------|
| Motor L Forward | 2 | L298N IN1 | Digital Out |
| Motor L Backward | 3 | L298N IN2 | Digital Out |
| Motor L Speed | 4 | L298N ENA | PWM Out |
| Motor R Forward | 5 | L298N IN3 | Digital Out |
| Motor R Backward | 6 | L298N IN4 | Digital Out |
| Motor R Speed | 7 | L298N ENB | PWM Out |
| US Front Trig | 8 | HC-SR04 | Digital Out |
| US Front Echo | 9 | HC-SR04 | Digital In |
| US Side Trig | 10 | HC-SR04 | Digital Out |
| US Side Echo | 11 | HC-SR04 | Digital In |
| Servo Head | 12 | SG90 | PWM Out |
| Servo Arm L | 13 | SG90 | PWM Out |
| Servo Arm R | 14 | SG90 | PWM Out |
| Status LED | 13 | LED | Digital Out |
| Bluetooth RX | 18 | HC-05 TX | Serial In |
| Bluetooth TX | 19 | HC-05 RX | Serial Out |
| LCD RS | 22 | LCD 16x2 | Digital Out |
| LCD Enable | 23 | LCD 16x2 | Digital Out |
| LCD D4 | 24 | LCD 16x2 | Digital Out |
| LCD D5 | 25 | LCD 16x2 | Digital Out |
| LCD D6 | 26 | LCD 16x2 | Digital Out |
| LCD D7 | 27 | LCD 16x2 | Digital Out |

## Especificações Técnicas

### Alimentação
- **Tensão Principal**: 7.4V (LiPo)
- **Tensão Lógica**: 5V (regulada)
- **Corrente Motores**: 2A máx (cada)
- **Corrente Total**: 5A máx
- **Autonomia**: 2-4 horas (depende do uso)

### Performance
- **Velocidade Máxima**: 0.5 m/s
- **Raio de Curva**: 0.3m
- **Detecção Obstáculos**: 2cm - 400cm
- **Ângulo Cabeça**: ±90°
- **Ângulo Braços**: 180°
- **Peso Total**: ~2kg

### Comunicação
- **Bluetooth**: 10m alcance
- **Serial**: 9600 baud
- **Protocolo**: Comandos ASCII simples
