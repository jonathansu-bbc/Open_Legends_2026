#include "motors.h"

void Motors::init() {

    delayMicroseconds(10);

    for (uint8_t i = 0; i < MOTOR_NUM; i++) { 
        pinMode(inA[i], OUTPUT);
        pinMode(inB[i], OUTPUT);
        pinMode(pwm[i], OUTPUT);
    }

    delayMicroseconds(10);

    for (uint8_t i = 0; i < MOTOR_NUM; i++) { 
        digitalWrite(inA[i], HIGH);
        digitalWrite(inB[i], HIGH);
        analogWrite(pwm[i], 255);
    }

    delayMicroseconds(10);
}

void Motors::move(float speed, float direction, float rotation) {

    for (uint8_t i = 0; i < MOTOR_NUM; i++) { 
        motorSpeeds[i] = rotation;
    }

    for (uint8_t i = 0; i < MOTOR_NUM; i++) {
        uint8_t ina = motorSpeeds[i] > 0 ? HIGH : LOW;
        uint8_t inb = motorSpeeds[i] < 0 ? HIGH : LOW;
        uint8_t speed = round(fabs(motorSpeeds[i]));
        digitalWrite(inA[i], ina);
        digitalWrite(inB[i], inb);
        analogWrite(pwm[i], speed);

        Serial.printf("Motor %d: A-%d, B-%d, PWM-%d\t", i, ina, inb, speed);
    }
    Serial.println();
}


//     float highest = -1.0f;
//     for (uint8_t i = 0; i < 4; i++) {
//         motorSpeeds[i] = -speed * cosf((motorAngles[i] - direction) * DEG_TO_RAD_F) - rotation;
//         highest = fmaxf(highest, fabsf(motorSpeeds[i]));
//     }
//     if (highest > 255.0f) {
//         for (uint8_t i = 0; i < 4; i++) {
//             motorSpeeds[i] *= 255.0f/highest;
//         }
//     }
//     FL.move((int16_t)roundf(motorSpeeds[0]));
//     FR.move((int16_t)roundf(motorSpeeds[1]));
//     BR.move((int16_t)roundf(motorSpeeds[2]));
//     BL.move((int16_t)roundf(motorSpeeds[3]));
//     for (int i = 0; i < 4; i++) {
//         Serial.print(motorSpeeds[i]);
//         Serial.print(" ");
//     }
//     Serial.println();
// }