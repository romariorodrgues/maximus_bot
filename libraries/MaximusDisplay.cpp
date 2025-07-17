/*
 * MaximusDisplay.cpp - Implementação da biblioteca para display do Robô Maximus
 */

#include "MaximusDisplay.h"

MaximusDisplay::MaximusDisplay(int rs, int en, int d4, int d5, int d6, int d7) {
    lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
    currentEyeState = NORMAL;
    lastBlink = 0;
    blinkInterval = 3000; // Piscar a cada 3 segundos
    isBlinking = false;
}

void MaximusDisplay::begin() {
    lcd->begin(16, 2);
    createCustomCharacters();
    showStartupMessage();
}

void MaximusDisplay::createCustomCharacters() {
    lcd->createChar(0, eyeNormal);
    lcd->createChar(1, eyeClosed);
    lcd->createChar(2, eyeHappy);
    lcd->createChar(3, eyeAngry);
}

void MaximusDisplay::showStartupMessage() {
    lcd->clear();
    lcd->setCursor(2, 0);
    lcd->print("MAXIMUS V2.0");
    lcd->setCursor(3, 1);
    lcd->print("INICIANDO...");
    delay(2000);
    
    lcd->clear();
    lcd->setCursor(4, 0);
    lcd->print("SISTEMAS");
    lcd->setCursor(6, 1);
    lcd->print("ONLINE");
    delay(1500);
}

void MaximusDisplay::updateEyes(EyeState state) {
    unsigned long currentTime = millis();
    
    // Verificar se é hora de piscar
    if (currentTime - lastBlink >= blinkInterval) {
        isBlinking = true;
        lastBlink = currentTime;
    }
    
    // Mostrar olhos piscando por 200ms
    if (isBlinking && (currentTime - lastBlink < 200)) {
        lcd->setCursor(3, 0);
        lcd->write(byte(1)); // Olho fechado
        lcd->print("        ");
        lcd->write(byte(1)); // Olho fechado
    } else {
        isBlinking = false;
        
        // Mostrar olhos baseado no estado
        lcd->setCursor(3, 0);
        switch (state) {
            case NORMAL:
                lcd->write(byte(0));
                lcd->print("        ");
                lcd->write(byte(0));
                break;
                
            case HAPPY:
                lcd->write(byte(2));
                lcd->print("   ^^   ");
                lcd->write(byte(2));
                break;
                
            case ANGRY:
                lcd->write(byte(3));
                lcd->print("   >>   ");
                lcd->write(byte(3));
                break;
                
            case SLEEPY:
                lcd->write(byte(1));
                lcd->print("   --   ");
                lcd->write(byte(1));
                break;
                
            case ALERT:
                lcd->write(byte(0));
                lcd->print("   !!   ");
                lcd->write(byte(0));
                break;
        }
    }
    
    currentEyeState = state;
}

void MaximusDisplay::showStatus(bool autonomous, int distance, int speed) {
    // Primeira linha - olhos (já gerenciada por updateEyes)
    updateEyes((EyeState)currentEyeState);
    
    // Segunda linha - status
    lcd->setCursor(0, 1);
    if (autonomous) {
        lcd->print("AUTO");
    } else {
        lcd->print("MAN ");
    }
    
    lcd->print(" D:");
    if (distance < 100) {
        lcd->print(" ");
    }
    if (distance < 10) {
        lcd->print(" ");
    }
    lcd->print(distance);
    lcd->print("cm");
    
    lcd->print(" V:");
    lcd->print(map(speed, 0, 255, 0, 99));
    lcd->print("%");
}

void MaximusDisplay::showMessage(String line1, String line2) {
    lcd->clear();
    
    // Centralizar texto na primeira linha
    int padding1 = (16 - line1.length()) / 2;
    lcd->setCursor(padding1, 0);
    lcd->print(line1);
    
    if (line2.length() > 0) {
        // Centralizar texto na segunda linha
        int padding2 = (16 - line2.length()) / 2;
        lcd->setCursor(padding2, 1);
        lcd->print(line2);
    }
}

void MaximusDisplay::setBlinkRate(unsigned long interval) {
    blinkInterval = interval;
}

void MaximusDisplay::forceBlink() {
    lastBlink = millis() - blinkInterval;
}

void MaximusDisplay::clearDisplay() {
    lcd->clear();
}

void MaximusDisplay::setEmotion(EyeState emotion) {
    currentEyeState = emotion;
}
