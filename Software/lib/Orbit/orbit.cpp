#include "orbit.h"

float Orbit::velocity(bool attackGoal, float attackGoalAngle, float ballAngle, float ballDist) {
    // float surgeAngle = attackGoal ? attackGoalAngle : 0.0f;
    float moveSpeed = -1.0f;
    float minorAngle = angleDiff(ballAngle, 0.0f);
    if (minorAngle < ATTACK_SURGE_ANGLE && ballDist < ATTACK_CLOSE_DISTANCE) { // surges and accelerates
        Serial.println("BOMBOCLAT");
        moveSpeed = constrain((moveSpeed + 0.5f), ATTACK_SLOW_SPEED, ATTACK_SURGE_SPEED); // maybe 150?
        return moveSpeed;
    } else {
        moveSpeed = 0.0f; // resets
    }

    // float m = (ATTACK_FAST_SPEED - ATTACK_SLOW_SPEED)/(ATTACK_FAR_DISTANCE - ATTACK_CLOSE_DISTANCE);
    // float line = m * (ballDist - ATTACK_CLOSE_DISTANCE) + ATTACK_SLOW_SPEED;
    // return constrain(line, ATTACK_SLOW_SPEED, ATTACK_FAST_SPEED);
    // float angleSpeed = constrain(0.416667f * minorAngle + 75.0f, ATTACK_SLOW_SPEED, ATTACK_FAST_SPEED);

    // float angleSpeed = constrain(1.247e-5f * powf((minorAngle - 180.0f), 3.0f) + 122.72657f, ATTACK_SLOW_SPEED, ATTACK_FAST_SPEED);
    // float distSpeed = constrain(4.47052e-6f * powf((ballDist - 100.0f), 3.0f) + 1.7f, ATTACK_MIN_SPEED_SCALE_FACTOR, ATTACK_MAX_SPEED_SCALE_FACTOR);
    
    // float angleFunction = 3.53025e-5f * powf(minorAngle - 90.0f, 3.0f) + 80.88168f;
    // float distFunction = 5.75866e-6f * powf((ballDist - ATTACK_FAR_DISTANCE), 3.0f) + 1.9331f;
    // float distSpeed = fmin(ATTACK_MAX_SPEED_SCALE_FACTOR, fmax(ATTACK_MIN_SPEED_SCALE_FACTOR, distFunction));
    // moveSpeed = constrain(angleFunction * distSpeed, ATTACK_SLOW_SPEED, ATTACK_FAST_SPEED);
    // return moveSpeed;

    return 90.0f;
}

float Orbit::direction(bool attackGoal, float attackGoalAngle, float ballAngle, float ballDist) {
    // float surgeAngle = attackGoal ? attackGoalAngle : 0.0f;
    float minorAngle = angleDiff(ballAngle, 0.0f);
    if (minorAngle < ATTACK_SURGE_ANGLE && ballDist < ATTACK_CLOSE_DISTANCE) {
        return attackGoalAngle;
    }
    float angleOffset = constrain(0.075f * minorAngle * minorAngle, ATTACK_MIN_OFFSET, ATTACK_MAX_OFFSET);
    // float distScaleFactor = constrain(8.83533e-15f * powf(ballDist - 269.13499f, 6.0f) + 0.0199401f, MIN_OFFSET_SCALE_FACTOR, MAX_OFFSET_SCALE_FACTOR);
    float numerator = 1.0f;
    float denominator = 1.0f + expf(0.1f * (ballDist - 75.0f));
    float distScaleFactor = constrain(numerator/denominator, ATTACK_MIN_ANGLE_SCALE_FACTOR, ATTACK_MAX_ANGLE_SCALE_FACTOR);
    float moveOffset = angleOffset * distScaleFactor;
    float moveAngle = normaliseAngle(ballAngle > 180.0f ? ballAngle - moveOffset : ballAngle + moveOffset);
    // Serial.println(moveAngle);
    return moveAngle;
}

void Orbit::update(const CameraData& cameraData) {
    orbitData.orbitSpeed = velocity(cameraData.attackGoal, cameraData.attackGoalAngle, cameraData.ballAngle, cameraData.ballDist);
    orbitData.orbitAngle = direction(cameraData.attackGoal, cameraData.attackGoalAngle, cameraData.ballAngle, cameraData.ballDist);
}