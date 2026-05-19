#ifndef MOTORS_H
#define MOTORS_H

#include "motor.h"
#include "common.h"

class Motors {
public:
    Motors() {}
    void init();
    void move(float speed, float direction, float rotation);

private:
    Motor FL = Motor(FL_INA, FL_INB, FL_PWM);
    Motor FR = Motor(FR_INA, FR_INB, FR_PWM);
    Motor BR = Motor(BR_INA, BR_INB, BR_PWM);
    Motor BL = Motor(BL_INA, BL_INB, BL_PWM);

    uint8_t inA[MOTOR_NUM] = {FR_INA, FL_INA, BL_INA, BR_INA};
    uint8_t inB[MOTOR_NUM] = {FR_INB, FL_INB, BL_INB, BR_INB};
    uint8_t pwm[MOTOR_NUM] = {FR_PWM, FL_PWM, BL_PWM, BR_PWM};


    float motorAngles[MOTOR_NUM] = {45.0f, 135.0f, 225.0f, 315.0f};
    float motorSpeeds[MOTOR_NUM] = {0.0f};
};

#endif