/*
 * MaximusDisplay.h - Biblioteca para controle do display do Robô Maximus
 * Esta biblioteca gerencia os "olhos" expressivos e informações do display
 */

#ifndef MAXIMUS_DISPLAY_H
#define MAXIMUS_DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class MaximusDisplay {
private:
    LiquidCrystal* lcd;
    int currentEyeState;
    unsigned long lastBlink;
    unsigned long blinkInterval;
    bool isBlinking;
    
    // Caracteres customizados para os olhos
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
    
    byte eyeClosed[8] = {
        B00000,
        B00000,
        B11111,
        B11111,
        B11111,
        B00000,
        B00000,
        B00000
    };
    
    byte eyeHappy[8] = {
        B00000,
        B00000,
        B01110,
        B11111,
        B11111,
        B11111,
        B01110,
        B00000
    };
    
    byte eyeAngry[8] = {
        B11000,
        B01100,
        B00110,
        B11111,
        B11111,
        B11111,
        B01110,
        B00000
    };

public:
    // Estados dos olhos
    enum EyeState {
        NORMAL = 0,
        HAPPY = 1,
        ANGRY = 2,
        SLEEPY = 3,
        ALERT = 4
    };
    
    MaximusDisplay(int rs, int en, int d4, int d5, int d6, int d7);
    void begin();
    void createCustomCharacters();
    void showStartupMessage();
    void updateEyes(EyeState state = NORMAL);
    void showStatus(bool autonomous, int distance, int speed);
    void showMessage(String line1, String line2 = "");
    void setBlinkRate(unsigned long interval);
    void forceBlink();
    void clearDisplay();
    void setEmotion(EyeState emotion);
};

#endif
