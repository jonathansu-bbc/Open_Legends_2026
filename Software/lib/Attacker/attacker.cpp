#include "attacker.h"

// PID attackGoalPID(GOAL_TRACK_P, I, GOAL_TRACK_D, ATTACK_GOAL_TRACK_MAX);
// PID attackHorizontalPID(HORIZONTAL_P, I, HORIZONTAL_D, MAX_CORRECTION);
// PID attackVerticalPID(VERTICAL_P, I, VERTICAL_D, MAX_CORRECTION);

void Attacker::init() {
    timer = millis();
}

void Attacker::update(const LSData& lsData, const CameraData& cameraData, const OrbitData& orbitData, float heading, float compassRot) {
    // float attackGoalRot = -attackGoalPID.update(normaliseHalfAngle(cameraData.attackGoalAngle), 0.0f);
    if (lsData.avoidAngle != -1.0f) { // Not in State 1
        movementValues[0] = lsData.stopOnLine ? 0.0f : AVOID_SPEED;
        movementValues[1] = lsData.stopOnLine ? 0.0f : lsData.avoidAngle;
    } else { // Add centering
        movementValues[0] = cameraData.ball ? orbitData.orbitSpeed : -25.0f;
        movementValues[1] = cameraData.ball ? orbitData.orbitAngle : normaliseAngle(180.0f - heading);
    }
    // movementValues[2] = cameraData.attackGoal ? attackGoalRot : compassRot;
}