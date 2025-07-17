/*
 * MaximusMotors.h - Biblioteca para controle dos motores do Robô Maximus
 * Gerencia motores DC das lagartas e servo motores da cabeça/braços
 */

#ifndef MAXIMUS_MOTORS_H
#define MAXIMUS_MOTORS_H

#include <Arduino.h>
#include <Servo.h>

class MaximusMotors {
private:
    // Pinos dos motores DC
    int leftForwardPin, leftBackwardPin, leftPWMPin;
    int rightForwardPin, rightBackwardPin, rightPWMPin;
    
    // Servos
    Servo servoHead, servoArmLeft, servoArmRight;
    int headPin, armLeftPin, armRightPin;
    
    // Posições atuais dos servos
    int headPosition;
    int armLeftPosition;
    int armRightPosition;
    
    // Configurações
    int currentSpeed;
    int maxSpeed;
    int minSpeed;
    
    // Segurança
    bool motorsEnabled;
    unsigned long lastMoveTime;

public:
    MaximusMotors(int lf, int lb, int lp, int rf, int rb, int rp, 
                  int head, int armL, int armR);
    
    void begin();
    void enableMotors(bool enable = true);
    
    // Controle dos motores DC
    void moveForward(int speed = -1);
    void moveBackward(int speed = -1);
    void turnLeft(int speed = -1);
    void turnRight(int speed = -1);
    void stop();
    void setSpeed(int speed);
    int getSpeed();
    
    // Controle dos servos
    void moveHead(int angle);
    void moveArmLeft(int angle);
    void moveArmRight(int angle);
    void moveBothArms(int leftAngle, int rightAngle);
    void centerHead();
    void centerArms();
    void waveArms();
    void lookAround();
    
    // Posições predefinidas
    void armsUp();
    void armsDown();
    void armsForward();
    void gestureHello();
    void gestureThinking();
    
    // Status
    int getHeadPosition();
    int getArmLeftPosition();
    int getArmRightPosition();
    bool areMotorsEnabled();
    
    // Segurança
    void emergencyStop();
    void resetPositions();
};

#endif
