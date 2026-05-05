#include "motor.h"

Motor::Motor(uint8_t ina, uint8_t inb, uint8_t pwm) { // Constructor for Motor class
    INA = ina;
    INB = inb;
    PWM = pwm;
}

void Motor::init() {
    pinMode(INA, OUTPUT);
    pinMode(INB, OUTPUT);
    pinMode(PWM, OUTPUT);
}

void Motor::move(int16_t speed) {
    if (speed > 0) {
        digitalWrite(INA, HIGH);
        digitalWrite(INB, LOW);
        analogWrite(PWM, constrain(abs(speed), 0, 255));
    } else if (speed < 0) {
        digitalWrite(INA, LOW);
        digitalWrite(INB, HIGH);
        analogWrite(PWM, constrain(abs(speed), 0, 255));
    } else {
        digitalWrite(INA, HIGH);
        digitalWrite(INB, HIGH);
        analogWrite(PWM, constrain(abs(speed), 0, 255));
    }
}