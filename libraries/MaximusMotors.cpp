/*
 * MaximusMotors.cpp - Implementação da biblioteca de motores do Robô Maximus
 */

#include "MaximusMotors.h"

MaximusMotors::MaximusMotors(int lf, int lb, int lp, int rf, int rb, int rp, 
                             int head, int armL, int armR) {
    leftForwardPin = lf;
    leftBackwardPin = lb;
    leftPWMPin = lp;
    rightForwardPin = rf;
    rightBackwardPin = rb;
    rightPWMPin = rp;
    
    headPin = head;
    armLeftPin = armL;
    armRightPin = armR;
    
    currentSpeed = 150;
    maxSpeed = 255;
    minSpeed = 50;
    
    headPosition = 90;
    armLeftPosition = 90;
    armRightPosition = 90;
    
    motorsEnabled = true;
    lastMoveTime = 0;
}

void MaximusMotors::begin() {
    // Configurar pinos dos motores DC
    pinMode(leftForwardPin, OUTPUT);
    pinMode(leftBackwardPin, OUTPUT);
    pinMode(leftPWMPin, OUTPUT);
    pinMode(rightForwardPin, OUTPUT);
    pinMode(rightBackwardPin, OUTPUT);
    pinMode(rightPWMPin, OUTPUT);
    
    // Inicializar servos
    servoHead.attach(headPin);
    servoArmLeft.attach(armLeftPin);
    servoArmRight.attach(armRightPin);
    
    // Posições iniciais
    resetPositions();
    
    // Parar motores
    stop();
}

void MaximusMotors::enableMotors(bool enable) {
    motorsEnabled = enable;
    if (!enable) {
        stop();
    }
}

void MaximusMotors::moveForward(int speed) {
    if (!motorsEnabled) return;
    
    if (speed == -1) speed = currentSpeed;
    speed = constrain(speed, minSpeed, maxSpeed);
    
    digitalWrite(leftForwardPin, HIGH);
    digitalWrite(leftBackwardPin, LOW);
    digitalWrite(rightForwardPin, HIGH);
    digitalWrite(rightBackwardPin, LOW);
    
    analogWrite(leftPWMPin, speed);
    analogWrite(rightPWMPin, speed);
    
    lastMoveTime = millis();
}

void MaximusMotors::moveBackward(int speed) {
    if (!motorsEnabled) return;
    
    if (speed == -1) speed = currentSpeed;
    speed = constrain(speed, minSpeed, maxSpeed);
    
    digitalWrite(leftForwardPin, LOW);
    digitalWrite(leftBackwardPin, HIGH);
    digitalWrite(rightForwardPin, LOW);
    digitalWrite(rightBackwardPin, HIGH);
    
    analogWrite(leftPWMPin, speed);
    analogWrite(rightPWMPin, speed);
    
    lastMoveTime = millis();
}

void MaximusMotors::turnLeft(int speed) {
    if (!motorsEnabled) return;
    
    if (speed == -1) speed = currentSpeed;
    speed = constrain(speed, minSpeed, maxSpeed);
    
    digitalWrite(leftForwardPin, LOW);
    digitalWrite(leftBackwardPin, HIGH);
    digitalWrite(rightForwardPin, HIGH);
    digitalWrite(rightBackwardPin, LOW);
    
    analogWrite(leftPWMPin, speed);
    analogWrite(rightPWMPin, speed);
    
    lastMoveTime = millis();
}

void MaximusMotors::turnRight(int speed) {
    if (!motorsEnabled) return;
    
    if (speed == -1) speed = currentSpeed;
    speed = constrain(speed, minSpeed, maxSpeed);
    
    digitalWrite(leftForwardPin, HIGH);
    digitalWrite(leftBackwardPin, LOW);
    digitalWrite(rightForwardPin, LOW);
    digitalWrite(rightBackwardPin, HIGH);
    
    analogWrite(leftPWMPin, speed);
    analogWrite(rightPWMPin, speed);
    
    lastMoveTime = millis();
}

void MaximusMotors::stop() {
    digitalWrite(leftForwardPin, LOW);
    digitalWrite(leftBackwardPin, LOW);
    digitalWrite(rightForwardPin, LOW);
    digitalWrite(rightBackwardPin, LOW);
    
    analogWrite(leftPWMPin, 0);
    analogWrite(rightPWMPin, 0);
}

void MaximusMotors::setSpeed(int speed) {
    currentSpeed = constrain(speed, minSpeed, maxSpeed);
}

int MaximusMotors::getSpeed() {
    return currentSpeed;
}

void MaximusMotors::moveHead(int angle) {
    angle = constrain(angle, 0, 180);
    servoHead.write(angle);
    headPosition = angle;
    delay(15); // Pequeno delay para estabilização
}

void MaximusMotors::moveArmLeft(int angle) {
    angle = constrain(angle, 0, 180);
    servoArmLeft.write(angle);
    armLeftPosition = angle;
    delay(15);
}

void MaximusMotors::moveArmRight(int angle) {
    angle = constrain(angle, 0, 180);
    servoArmRight.write(angle);
    armRightPosition = angle;
    delay(15);
}

void MaximusMotors::moveBothArms(int leftAngle, int rightAngle) {
    leftAngle = constrain(leftAngle, 0, 180);
    rightAngle = constrain(rightAngle, 0, 180);
    
    servoArmLeft.write(leftAngle);
    servoArmRight.write(rightAngle);
    
    armLeftPosition = leftAngle;
    armRightPosition = rightAngle;
    
    delay(15);
}

void MaximusMotors::centerHead() {
    moveHead(90);
}

void MaximusMotors::centerArms() {
    moveBothArms(90, 90);
}

void MaximusMotors::waveArms() {
    for (int i = 0; i < 3; i++) {
        moveBothArms(45, 135);
        delay(300);
        moveBothArms(135, 45);
        delay(300);
    }
    centerArms();
}

void MaximusMotors::lookAround() {
    int originalPosition = headPosition;
    
    moveHead(45);   // Olhar para a direita
    delay(500);
    moveHead(135);  // Olhar para a esquerda
    delay(500);
    moveHead(90);   // Voltar ao centro
    delay(300);
}

void MaximusMotors::armsUp() {
    moveBothArms(45, 135);
}

void MaximusMotors::armsDown() {
    moveBothArms(135, 45);
}

void MaximusMotors::armsForward() {
    moveBothArms(90, 90);
}

void MaximusMotors::gestureHello() {
    // Acenar com o braço direito
    for (int i = 0; i < 4; i++) {
        moveArmRight(45);
        delay(200);
        moveArmRight(135);
        delay(200);
    }
    moveArmRight(90); // Voltar à posição neutra
}

void MaximusMotors::gestureThinking() {
    // Mão na cabeça - gesto pensativo
    moveHead(75);
    moveArmRight(120);
    delay(2000);
    
    // Voltar à posição normal
    centerHead();
    centerArms();
}

int MaximusMotors::getHeadPosition() {
    return headPosition;
}

int MaximusMotors::getArmLeftPosition() {
    return armLeftPosition;
}

int MaximusMotors::getArmRightPosition() {
    return armRightPosition;
}

bool MaximusMotors::areMotorsEnabled() {
    return motorsEnabled;
}

void MaximusMotors::emergencyStop() {
    stop();
    enableMotors(false);
}

void MaximusMotors::resetPositions() {
    centerHead();
    centerArms();
    delay(500); // Tempo para os servos se posicionarem
}
