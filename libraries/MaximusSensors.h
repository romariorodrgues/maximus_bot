/*
 * MaximusSensors.h - Biblioteca para gerenciamento dos sensores do Robô Maximus
 * Controla sensores ultrassônicos e outros sensores do robô
 */

#ifndef MAXIMUS_SENSORS_H
#define MAXIMUS_SENSORS_H

#include <Arduino.h>

class MaximusSensors {
private:
    // Pinos dos sensores ultrassônicos
    int frontTrigPin, frontEchoPin;
    int sideTrigPin, sideEchoPin;
    
    // Últimas leituras
    long frontDistance;
    long sideDistance;
    
    // Configurações
    int safeDistance;
    int maxDistance;
    
    // Timing
    unsigned long lastRead;
    int readInterval;
    
    // Filtros
    long frontReadings[5];
    long sideReadings[5];
    int readingIndex;
    
    // Métodos auxiliares
    long readUltrasonic(int trigPin, int echoPin);
    long getFilteredReading(long readings[]);
    void updateReadings();

public:
    MaximusSensors(int frontTrig, int frontEcho, int sideTrig, int sideEcho);
    
    void begin();
    void setSafeDistance(int distance);
    void setReadInterval(int interval);
    
    // Leituras principais
    void updateSensors();
    long getFrontDistance();
    long getSideDistance();
    long getMinDistance();
    
    // Verificações de segurança
    bool isFrontClear();
    bool isSideClear();
    bool isPathClear();
    bool hasObstacle();
    
    // Navegação
    bool shouldTurnLeft();
    bool shouldTurnRight();
    int getBestDirection(); // 0=frente, 1=esquerda, 2=direita, 3=trás
    
    // Detecção avançada
    bool isCorner();
    bool isDeadEnd();
    bool isNarrowPassage();
    
    // Calibração e configuração
    void calibrate();
    void setMaxDistance(int distance);
    int getSafeDistance();
    
    // Debug
    void printReadings();
    String getStatusString();
};

#endif
