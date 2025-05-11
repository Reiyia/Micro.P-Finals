#include "Arduino.h"
#include "esp32-hal-ledc.h"
#include <Wire.h>

// Motor A
int motorA1 = 12;
int motorA2 = 27;
int enblA = 13;
int IRR = 4;
int IRRVal;

// Motor B
int motorB1 = 26;
int motorB2 = 25;
int enblB = 14;
int IRL = 5;
int IRLVal;

// Motor Booster
int POT = 15;

// PWM Setup
const int freq = 30000;
const int pwm1 = 0;
const int pwm2 = 1;
const int resolution = 8;
int dutyCycle1 = 160;
int dutyCycle2 = 170;

void setup() {
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(enblA, INPUT);
    pinMode(IRR, INPUT_PULLUP);

    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(enblB, INPUT);
    pinMode(IRL, INPUT_PULLUP);

    // PWM Setup
    ledcSetup(pwm1, freq, resolution);
    ledcSetup(pwm2, freq, resolution);

    ledcAttachPin(enblA, pwm1);
    ledcAttachPin(enblB, pwm2);

    ledcWrite(pwm1, dutyCycle1);
    ledcWrite(pwm2, dutyCycle2);

    MotorAForward();
    MotorBForward();
}

void MotorAForward() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
}

void MotorBForward() {
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
}

void MotorAStop() {
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
}

void MotorBStop() {
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
}

void loop() {
    IRRVal = digitalRead(IRR);
    IRLVal = digitalRead(IRL);

    if (IRRVal == LOW) {
        dutyCycle1 = max(0, dutyCycle1 - 20);  // Prevent negative values
        ledcWrite(pwm1, dutyCycle1);
    } else {
        dutyCycle1 = min(255, dutyCycle1 + 20);  // Prevent overflow
        ledcWrite(pwm1, dutyCycle1);
    }

    if (IRLVal == LOW) {
        dutyCycle2 = max(0, dutyCycle2 - 20);  // Prevent negative values
        ledcWrite(pwm2, dutyCycle2);
    } else {
        dutyCycle2 = min(255, dutyCycle2 + 20);  // Prevent overflow
        ledcWrite(pwm2, dutyCycle2);
    }
}