/*
 * MaximusSensors.cpp - Implementação da biblioteca de sensores do Robô Maximus
 */

#include "MaximusSensors.h"

MaximusSensors::MaximusSensors(int frontTrig, int frontEcho, int sideTrig, int sideEcho) {
    frontTrigPin = frontTrig;
    frontEchoPin = frontEcho;
    sideTrigPin = sideTrig;
    sideEchoPin = sideEcho;
    
    frontDistance = 0;
    sideDistance = 0;
    safeDistance = 20;
    maxDistance = 400;
    lastRead = 0;
    readInterval = 50;
    readingIndex = 0;
    
    // Inicializar arrays de filtro
    for (int i = 0; i < 5; i++) {
        frontReadings[i] = 0;
        sideReadings[i] = 0;
    }
}

void MaximusSensors::begin() {
    pinMode(frontTrigPin, OUTPUT);
    pinMode(frontEchoPin, INPUT);
    pinMode(sideTrigPin, OUTPUT);
    pinMode(sideEchoPin, INPUT);
    
    // Fazer leituras iniciais
    for (int i = 0; i < 10; i++) {
        updateSensors();
        delay(50);
    }
}

void MaximusSensors::setSafeDistance(int distance) {
    safeDistance = constrain(distance, 5, 100);
}

void MaximusSensors::setReadInterval(int interval) {
    readInterval = constrain(interval, 20, 500);
}

long MaximusSensors::readUltrasonic(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH, 30000); // Timeout de 30ms
    
    if (duration == 0) {
        return maxDistance; // Se timeout, assumir distância máxima
    }
    
    long distance = duration * 0.034 / 2;
    
    // Filtrar leituras inválidas
    if (distance < 2 || distance > maxDistance) {
        return maxDistance;
    }
    
    return distance;
}

long MaximusSensors::getFilteredReading(long readings[]) {
    // Calcular média dos últimos 5 valores, ignorando extremos
    long total = 0;
    long min_val = readings[0];
    long max_val = readings[0];
    
    for (int i = 0; i < 5; i++) {
        total += readings[i];
        if (readings[i] < min_val) min_val = readings[i];
        if (readings[i] > max_val) max_val = readings[i];
    }
    
    // Remover valor mínimo e máximo, calcular média dos 3 restantes
    total = total - min_val - max_val;
    return total / 3;
}

void MaximusSensors::updateReadings() {
    frontReadings[readingIndex] = readUltrasonic(frontTrigPin, frontEchoPin);
    sideReadings[readingIndex] = readUltrasonic(sideTrigPin, sideEchoPin);
    
    readingIndex = (readingIndex + 1) % 5;
    
    frontDistance = getFilteredReading(frontReadings);
    sideDistance = getFilteredReading(sideReadings);
}

void MaximusSensors::updateSensors() {
    unsigned long currentTime = millis();
    
    if (currentTime - lastRead >= readInterval) {
        updateReadings();
        lastRead = currentTime;
    }
}

long MaximusSensors::getFrontDistance() {
    return frontDistance;
}

long MaximusSensors::getSideDistance() {
    return sideDistance;
}

long MaximusSensors::getMinDistance() {
    return min(frontDistance, sideDistance);
}

bool MaximusSensors::isFrontClear() {
    return frontDistance > safeDistance;
}

bool MaximusSensors::isSideClear() {
    return sideDistance > safeDistance;
}

bool MaximusSensors::isPathClear() {
    return isFrontClear() && isSideClear();
}

bool MaximusSensors::hasObstacle() {
    return !isFrontClear() || !isSideClear();
}

bool MaximusSensors::shouldTurnLeft() {
    return !isFrontClear() && isSideClear();
}

bool MaximusSensors::shouldTurnRight() {
    return !isFrontClear() && !isSideClear();
}

int MaximusSensors::getBestDirection() {
    if (isFrontClear()) {
        return 0; // Frente
    } else if (isSideClear()) {
        return 1; // Esquerda
    } else {
        return 2; // Direita
    }
}

bool MaximusSensors::isCorner() {
    return !isFrontClear() && !isSideClear();
}

bool MaximusSensors::isDeadEnd() {
    // Considera dead-end se frente e lado estão bloqueados
    return frontDistance < safeDistance && sideDistance < safeDistance;
}

bool MaximusSensors::isNarrowPassage() {
    // Passagem estreita se lado está próximo mas frente está livre
    return isFrontClear() && (sideDistance < safeDistance * 1.5);
}

void MaximusSensors::calibrate() {
    Serial.println("Calibrando sensores...");
    
    // Fazer múltiplas leituras para estabilizar
    for (int i = 0; i < 20; i++) {
        updateReadings();
        Serial.print("Frente: ");
        Serial.print(frontDistance);
        Serial.print("cm, Lado: ");
        Serial.print(sideDistance);
        Serial.println("cm");
        delay(100);
    }
    
    Serial.println("Calibração concluída!");
}

void MaximusSensors::setMaxDistance(int distance) {
    maxDistance = constrain(distance, 50, 500);
}

int MaximusSensors::getSafeDistance() {
    return safeDistance;
}

void MaximusSensors::printReadings() {
    Serial.print("Sensores - Frente: ");
    Serial.print(frontDistance);
    Serial.print("cm, Lado: ");
    Serial.print(sideDistance);
    Serial.print("cm");
    
    if (!isFrontClear()) {
        Serial.print(" [OBSTÁCULO FRENTE]");
    }
    if (!isSideClear()) {
        Serial.print(" [OBSTÁCULO LADO]");
    }
    
    Serial.println();
}

String MaximusSensors::getStatusString() {
    String status = "F:";
    status += String(frontDistance);
    status += "cm L:";
    status += String(sideDistance);
    status += "cm";
    
    if (hasObstacle()) {
        status += " OBST";
    } else {
        status += " LIVRE";
    }
    
    return status;
}
