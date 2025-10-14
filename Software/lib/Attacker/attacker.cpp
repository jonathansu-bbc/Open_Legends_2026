#include "attacker.h"

PID attackGoalPID(GOAL_TRACK_P, INTEGRAL, GOAL_TRACK_D, ATTACK_GOAL_TRACK_MAX);
// PID attackHorizontalPID(HORIZONTAL_P, INTEGRAL, HORIZONTAL_D, MAX_CORRECTION);
// PID attackVerticalPID(VERTICAL_P, INTEGRAL, VERTICAL_D, MAX_CORRECTION);

void Attacker::init() {
    timer = millis();
}

void Attacker::update(const LSData& lsData, const CameraData& cameraData, const OrbitData& orbitData, float compassRot) {
    float attackGoalRot = -attackGoalPID.update(normaliseHalfAngle(cameraData.attackGoalAngle), 0.0f);
    if (lsData.avoidAngle != -1.0f) {
        if (cameraData.ball) {
            movementValues[0] = lsData.stopOnLine ? 0.0f : AVOID_SPEED;
            movementValues[1] = lsData.stopOnLine ? 0.0f : lsData.avoidAngle;
        } else {
            movementValues[0] = AVOID_SPEED;
            movementValues[1] = lsData.avoidAngle;
        }
    } else {
        movementValues[0] = cameraData.ball ? orbitData.orbitSpeed : -25.0f;
        movementValues[1] = cameraData.ball ? orbitData.orbitAngle : 0.0f;
    }
    movementValues[2] = cameraData.attackGoal ? attackGoalRot : compassRot;
}