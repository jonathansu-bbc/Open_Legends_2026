#include "orbit.h"

float Orbit::speed(bool ball, bool attackGoal, float attackGoalAngle, float ballAngle, float ballDist) {
    // float surgeAngle = attackGoal ? attackGoalAngle : 0.0f;
    // float minorAngle = angleDiff(ballAngle, 0.0f);
    // if (minorAngle < ATTACK_SURGE_ANGLE && ballDist < ATTACK_CLOSE_DISTANCE) { // Surges and accelerates
    //     moveSpeed = constrain(moveSpeed + 0.5f, ATTACK_SLOW_SPEED, ATTACK_SURGE_SPEED);
    //     return moveSpeed;
    // } else {
    //     moveSpeed = -1.0f;
    // }
    // float m = (ATTACK_FAST_SPEED - ATTACK_SLOW_SPEED)/(ATTACK_FAR_DISTANCE - ATTACK_CLOSE_DISTANCE);
    // float line = m * (ballDist - ATTACK_CLOSE_DISTANCE) + ATTACK_SLOW_SPEED;
    // moveSpeed = constrain(line, ATTACK_SLOW_SPEED, ATTACK_FAST_SPEED);
    moveSpeed = ball ? 20.0f : 0.0f;
    return moveSpeed;
}

float Orbit::angle(bool attackGoal, float attackGoalAngle, float ballAngle, float ballDist) {
    float surgeAngle = attackGoal ? attackGoalAngle : 0.0f;
    float minorAngle = angleDiff(ballAngle, 0.0f);
    if (minorAngle < ATTACK_SURGE_ANGLE && ballDist < ATTACK_CLOSE_DISTANCE) {
        return surgeAngle;
    }
    float angleOffset = constrain(0.075f * minorAngle * minorAngle, 0.0f, ORBIT_MAX_OFFSET);
    float numerator = 1.0f;
    float denominator = expf(0.1f * (ballDist - 75.0f)) + 1.0f;
    float distScaleFactor = constrain(numerator/denominator, ORBIT_MIN_MULTIPLIER, ORBIT_MAX_MULTIPLIER);
    float moveOffset = angleOffset * distScaleFactor;
    float moveAngle = ballAngle > 180.0f ? ballAngle - moveOffset : ballAngle + moveOffset;
    return normaliseAngle(moveAngle);
}

void Orbit::update(const CameraData& cameraData) {
    orbitData.orbitSpeed = speed(cameraData.ball, cameraData.attackGoal, cameraData.attackGoalAngle, cameraData.ballAngle, cameraData.ballDist);
    orbitData.orbitAngle = angle(cameraData.attackGoal, cameraData.attackGoalAngle, cameraData.ballAngle, cameraData.ballDist);
}