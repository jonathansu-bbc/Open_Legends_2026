#include "PID.h"

// Proportional: Multiplies error by kp. Speeds up response but can cause oscillations
// Integral: Sums error over time and multiplies it by ki. Excessive gain makes controller unstable
// Derivative: Multiplies rate of change of error by kd. Stops overshooting

PID::PID(float p, float i, float d, float absoluteMax) {
    kp = p;
    ki = i;
    kd = d;
    absMax = absoluteMax;
    lastTime = micros();
}

float PID::update(float input, float setpoint, float modulus) {
    float derivative;
    float error = setpoint - input;
    unsigned long currentTime = micros();
    float elapsedTime = (currentTime - lastTime) / 1000000.0f;
    lastTime = currentTime;
    integral += elapsedTime * error;
    if (modulus != 0.0f) {
        float difference = (error - lastError);
        if (difference < -modulus) {
            difference += modulus;
        } else if (difference > modulus) {
            difference -= modulus;
        }
        derivative = difference / elapsedTime;
    } else {
        derivative = -(error - lastError) / elapsedTime; // ? why -
    }
    lastError = error;
    float correction = kp * error + ki * integral - kd * derivative;
    return absMax == 0.0f ? correction : constrain(correction, -absMax, absMax);
}