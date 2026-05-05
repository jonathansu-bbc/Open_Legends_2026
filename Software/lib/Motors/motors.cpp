#include "motors.h"

void Motors::init() {
    FL.init();
    FR.init();
    BR.init();
    BL.init();
}

void Motors::move(float speed, float direction, float rotation) {
    float highest = -1.0f;
    for (uint8_t i = 0; i < 4; i++) {
        motorSpeeds[i] = -speed * cosf((motorAngles[i] - direction) * DEG_TO_RAD_F) - rotation;
        highest = fmaxf(highest, fabsf(motorSpeeds[i]));
    }
    if (highest > 255.0f) {
        for (uint8_t i = 0; i < 4; i++) {
            motorSpeeds[i] *= 255.0f/highest;
        }
    }
    FL.move((int16_t)roundf(motorSpeeds[0]));
    FR.move((int16_t)roundf(motorSpeeds[1]));
    BR.move((int16_t)roundf(motorSpeeds[2]));
    BL.move((int16_t)roundf(motorSpeeds[3]));
    for (int i = 0; i < 4; i++) {
        Serial.print(motorSpeeds[i]);
        Serial.print(" ");
    }
    Serial.println();
}