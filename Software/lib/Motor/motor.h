#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "definitions.h"
#include "PID.h"

class Motor {
public:
    Motor(uint8_t ina, uint8_t inb, uint8_t pwm);
    void init();
    void move(float speed);

private:
    uint8_t INA, INB, PWM;

    float currentSpeed;
    PID motorPID = PID(MOTOR_KP, MOTOR_KI, MOTOR_KD, MOTOR_ABS_MAX);
};

#endif