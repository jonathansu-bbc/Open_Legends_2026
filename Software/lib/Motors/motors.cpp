#include "motors.h"

void Motors::init() {
    FL.init();
    FR.init();
    BR.init();
    BL.init();
}

void Motors::move(float speed, float dir, float rot) {
    float highest = -1.0f;
    for (uint8_t i = 0; i < 4; i++) {
        motorSpeeds[i] = -speed * cosf((45.0f + float(i) * 90.0f - dir) * DEG_TO_RAD_F) - rot;
        highest = fmax(highest, fabs(motorSpeeds[i]));
    }
    // float highest = fmax(fmax(fmax(fabs(motorSpeeds[0]), fabs(motorSpeeds[1])), fabs(motorSpeeds[2])), fabs(motorSpeeds[3]));
    if (highest > 255.0f) {
        for (uint8_t i = 0; i < 4; i++) {
            motorSpeeds[i] *= 255.0f/highest;
        }
    }
    FL.move((int16_t)roundf(motorSpeeds[0]));
    FR.move((int16_t)roundf(motorSpeeds[1]));
    BR.move((int16_t)roundf(motorSpeeds[2]));
    BL.move((int16_t)roundf(motorSpeeds[3]));
}