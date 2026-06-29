#include "motors.h"

// Motors::Motors()
// {
    
// }

void Motors::init() {
    for (uint8_t i = 0; i < MOTOR_NUM; i++) { 
        motor[i].init();
    }
}

void Motors::move(float speed, float direction, float rotation) {
    
    // for (uint8_t i = 0; i < MOTOR_NUM; i++) { 
    //     motorSpeeds[i] = rotation;
    // }

    float highest = -1.0f;
    for (uint8_t i = 0; i < 4; i++) {
        motorSpeeds[i] = -speed * cosf((motorAngles[i] - direction) * DEG_TO_RAD_F) - rotation;
        highest = fmaxf(highest, fabsf(motorSpeeds[i]));
    }
    if (highest > 100.0f) {
        for (uint8_t i = 0; i < 4; i++) {
            motorSpeeds[i] *= 100.0f/highest;
        }
    }
    
    // for (int i = 0; i < 4; i++) {
    //     Serial.print(motorSpeeds[i]);
    //     Serial.print(" ");
    // }
    // Serial.println();

    for (uint8_t i = 0; i < MOTOR_NUM; i++) {
        motor[i].move(constrain(motorSpeeds[i], -100.0f, 100.0f));
    }
    
    // FL.move((int16_t)roundf(motorSpeeds[0]));
    // FR.move((int16_t)roundf(motorSpeeds[1]));
    // BR.move((int16_t)roundf(motorSpeeds[2]));
    // BL.move((int16_t)roundf(motorSpeeds[3]));
    // for (int i = 0; i < 4; i++) {
    //     Serial.print(motorSpeeds[i]);
    //     Serial.print(" ");
    // }
    // Serial.println();
}