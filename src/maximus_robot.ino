/*
 * Projeto Robô Maximus - Código Principal
 * Robô autônomo com controle remoto, sensores ultrassônicos,
 * display para olhos, servo motores para cabeça e braços
 * 
 * Autor: Projeto Maximus
 * Data: Julho 2025
 * Plataforma: Arduino Mega 2560
 */

#include <Servo.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// ===== DEFINIÇÕES DE PINOS =====
// Motores DC das lagartas (Motor Driver L298N)
#define MOTOR_LEFT_FORWARD    2
#define MOTOR_LEFT_BACKWARD   3
#define MOTOR_LEFT_PWM        4
#define MOTOR_RIGHT_FORWARD   5
#define MOTOR_RIGHT_BACKWARD  6
#define MOTOR_RIGHT_PWM       7

// Sensores Ultrassônicos HC-SR04
#define ULTRASONIC_FRONT_TRIG 8
#define ULTRASONIC_FRONT_ECHO 9
#define ULTRASONIC_SIDE_TRIG  10
#define ULTRASONIC_SIDE_ECHO  11

// Servo Motores
#define SERVO_HEAD_PIN        12
#define SERVO_ARM_LEFT_PIN    13
#define SERVO_ARM_RIGHT_PIN   14

// Display LCD 16x2 para os "olhos"
#define LCD_RS    22
#define LCD_EN    23
#define LCD_D4    24
#define LCD_D5    25
#define LCD_D6    26
#define LCD_D7    27

// Bluetooth HC-05 para controle remoto
#define BT_RX     18
#define BT_TX     19

// LED indicador de status
#define STATUS_LED 13

// ===== OBJETOS E VARIÁVEIS =====
Servo servoHead;
Servo servoArmLeft;
Servo servoArmRight;
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
SoftwareSerial bluetooth(BT_RX, BT_TX);

// Variáveis de controle
bool autonomousMode = true;
bool remoteControlMode = false;
int headPosition = 90;        // Posição central da cabeça
int armLeftPosition = 90;     // Posição central do braço esquerdo
int armRightPosition = 90;    // Posição central do braço direito
int motorSpeed = 150;         // Velocidade dos motores (0-255)

// Variáveis dos sensores
long frontDistance = 0;
long sideDistance = 0;
const int SAFE_DISTANCE = 20; // Distância segura em cm

// Variáveis de timing
unsigned long lastSensorRead = 0;
unsigned long lastEyeUpdate = 0;
unsigned long lastHeadMove = 0;
const int SENSOR_INTERVAL = 100;
const int EYE_INTERVAL = 500;
const int HEAD_INTERVAL = 2000;

// Estados dos olhos
int eyeState = 0;
char customEyes[8][8] = {
  {0x00,0x0A,0x1F,0x1F,0x0E,0x04,0x00,0x00}, // Olho normal
  {0x00,0x00,0x0A,0x1F,0x1F,0x0E,0x04,0x00}, // Piscada
};

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  // Inicializar display LCD
  lcd.begin(16, 2);
  lcd.print("MAXIMUS ONLINE");
  delay(1000);
  
  // Configurar pinos dos motores
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  
  // Configurar sensores ultrassônicos
  pinMode(ULTRASONIC_FRONT_TRIG, OUTPUT);
  pinMode(ULTRASONIC_FRONT_ECHO, INPUT);
  pinMode(ULTRASONIC_SIDE_TRIG, OUTPUT);
  pinMode(ULTRASONIC_SIDE_ECHO, INPUT);
  
  // Configurar LED de status
  pinMode(STATUS_LED, OUTPUT);
  
  // Inicializar servo motores
  servoHead.attach(SERVO_HEAD_PIN);
  servoArmLeft.attach(SERVO_ARM_LEFT_PIN);
  servoArmRight.attach(SERVO_ARM_RIGHT_PIN);
  
  // Posição inicial dos servos
  servoHead.write(headPosition);
  servoArmLeft.write(armLeftPosition);
  servoArmRight.write(armRightPosition);
  
  delay(500);
  
  // Criar caracteres personalizados para os olhos
  createCustomEyes();
  
  Serial.println("Robô Maximus inicializado!");
  Serial.println("Comandos: F(frente), B(trás), L(esquerda), R(direita), S(parar)");
  Serial.println("A(autônomo), M(manual), H(mover cabeça), U(braços cima), D(braços baixo)");
}

void loop() {
  unsigned long currentTime = millis();
  
  // Verificar comandos do controle remoto
  if (bluetooth.available()) {
    handleRemoteControl();
  }
  
  // Verificar comandos do Serial Monitor
  if (Serial.available()) {
    handleSerialControl();
  }
  
  // Atualizar sensores
  if (currentTime - lastSensorRead >= SENSOR_INTERVAL) {
    readSensors();
    lastSensorRead = currentTime;
  }
  
  // Atualizar olhos
  if (currentTime - lastEyeUpdate >= EYE_INTERVAL) {
    updateEyes();
    lastEyeUpdate = currentTime;
  }
  
  // Movimento autônomo da cabeça
  if (currentTime - lastHeadMove >= HEAD_INTERVAL && autonomousMode) {
    moveHeadAutonomous();
    lastHeadMove = currentTime;
  }
  
  // Modo autônomo
  if (autonomousMode) {
    autonomousBehavior();
  }
  
  // Piscar LED de status
  digitalWrite(STATUS_LED, (millis() / 500) % 2);
}

// ===== FUNÇÕES DE MOVIMENTO =====
void moveForward() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_LEFT_PWM, motorSpeed);
  analogWrite(MOTOR_RIGHT_PWM, motorSpeed);
}

void moveBackward() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  analogWrite(MOTOR_LEFT_PWM, motorSpeed);
  analogWrite(MOTOR_RIGHT_PWM, motorSpeed);
}

void turnLeft() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_LEFT_PWM, motorSpeed);
  analogWrite(MOTOR_RIGHT_PWM, motorSpeed);
}

void turnRight() {
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  analogWrite(MOTOR_LEFT_PWM, motorSpeed);
  analogWrite(MOTOR_RIGHT_PWM, motorSpeed);
}

void stopMotors() {
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(MOTOR_LEFT_PWM, 0);
  analogWrite(MOTOR_RIGHT_PWM, 0);
}

// ===== FUNÇÕES DOS SENSORES =====
void readSensors() {
  frontDistance = readUltrasonic(ULTRASONIC_FRONT_TRIG, ULTRASONIC_FRONT_ECHO);
  sideDistance = readUltrasonic(ULTRASONIC_SIDE_TRIG, ULTRASONIC_SIDE_ECHO);
}

long readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  
  return distance;
}

// ===== COMPORTAMENTO AUTÔNOMO =====
void autonomousBehavior() {
  if (frontDistance > 0 && frontDistance < SAFE_DISTANCE) {
    // Obstáculo à frente - parar e desviar
    stopMotors();
    delay(100);
    
    // Verificar melhor direção para virar
    if (sideDistance > SAFE_DISTANCE) {
      turnLeft();
      delay(500);
    } else {
      turnRight();
      delay(800);
    }
  } else if (frontDistance >= SAFE_DISTANCE || frontDistance == 0) {
    // Caminho livre - mover para frente
    moveForward();
  }
}

// ===== CONTROLE REMOTO =====
void handleRemoteControl() {
  char command = bluetooth.read();
  processCommand(command);
}

void handleSerialControl() {
  char command = Serial.read();
  processCommand(command);
}

void processCommand(char command) {
  switch (command) {
    case 'F':
    case 'f':
      autonomousMode = false;
      moveForward();
      Serial.println("Movendo para frente");
      break;
      
    case 'B':
    case 'b':
      autonomousMode = false;
      moveBackward();
      Serial.println("Movendo para trás");
      break;
      
    case 'L':
    case 'l':
      autonomousMode = false;
      turnLeft();
      Serial.println("Virando à esquerda");
      break;
      
    case 'R':
    case 'r':
      autonomousMode = false;
      turnRight();
      Serial.println("Virando à direita");
      break;
      
    case 'S':
    case 's':
      stopMotors();
      Serial.println("Parando");
      break;
      
    case 'A':
    case 'a':
      autonomousMode = true;
      Serial.println("Modo autônomo ativado");
      break;
      
    case 'M':
    case 'm':
      autonomousMode = false;
      stopMotors();
      Serial.println("Modo manual ativado");
      break;
      
    case 'H':
    case 'h':
      moveHeadRandom();
      break;
      
    case 'U':
    case 'u':
      moveArmsUp();
      break;
      
    case 'D':
    case 'd':
      moveArmsDown();
      break;
      
    case '+':
      motorSpeed = min(255, motorSpeed + 25);
      Serial.print("Velocidade: ");
      Serial.println(motorSpeed);
      break;
      
    case '-':
      motorSpeed = max(50, motorSpeed - 25);
      Serial.print("Velocidade: ");
      Serial.println(motorSpeed);
      break;
  }
}

// ===== FUNÇÕES DOS SERVO MOTORES =====
void moveHeadAutonomous() {
  int newPosition = random(45, 135);
  servoHead.write(newPosition);
  headPosition = newPosition;
}

void moveHeadRandom() {
  int newPosition = random(0, 180);
  servoHead.write(newPosition);
  headPosition = newPosition;
  Serial.print("Cabeça movida para: ");
  Serial.println(newPosition);
}

void moveArmsUp() {
  armLeftPosition = 45;
  armRightPosition = 135;
  servoArmLeft.write(armLeftPosition);
  servoArmRight.write(armRightPosition);
  Serial.println("Braços levantados");
}

void moveArmsDown() {
  armLeftPosition = 135;
  armRightPosition = 45;
  servoArmLeft.write(armLeftPosition);
  servoArmRight.write(armRightPosition);
  Serial.println("Braços abaixados");
}

// ===== FUNÇÕES DO DISPLAY =====
void createCustomEyes() {
  // Caractere personalizado para olhos normais
  byte eyeNormal[8] = {
    B00000,
    B01110,
    B11111,
    B11111,
    B11111,
    B01110,
    B00000,
    B00000
  };
  
  // Caractere personalizado para piscada
  byte eyeBlink[8] = {
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000
  };
  
  lcd.createChar(0, eyeNormal);
  lcd.createChar(1, eyeBlink);
}

void updateEyes() {
  lcd.clear();
  
  // Primeira linha - olhos
  lcd.setCursor(3, 0);
  if (eyeState == 0) {
    lcd.write(byte(0)); // Olho esquerdo normal
    lcd.print("    ");
    lcd.write(byte(0)); // Olho direito normal
  } else {
    lcd.write(byte(1)); // Olho esquerdo piscando
    lcd.print("    ");
    lcd.write(byte(1)); // Olho direito piscando
  }
  
  // Segunda linha - informações
  lcd.setCursor(0, 1);
  if (autonomousMode) {
    lcd.print("AUTO ");
  } else {
    lcd.print("MANUAL ");
  }
  lcd.print("D:");
  lcd.print(frontDistance);
  lcd.print("cm");
  
  // Alternar estado dos olhos (piscar ocasionalmente)
  if (random(10) < 2) {
    eyeState = 1 - eyeState;
  }
}

// ===== FUNÇÃO DE DEBUG =====
void printSensorData() {
  Serial.print("Frente: ");
  Serial.print(frontDistance);
  Serial.print("cm | Lado: ");
  Serial.print(sideDistance);
  Serial.print("cm | Modo: ");
  Serial.print(autonomousMode ? "AUTO" : "MANUAL");
  Serial.print(" | Cabeça: ");
  Serial.print(headPosition);
  Serial.println("°");
}
