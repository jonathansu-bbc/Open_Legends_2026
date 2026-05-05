#include "defender.h"

PID defendGoalPID(GOAL_TRACK_P, I, GOAL_TRACK_D, DEFEND_GOAL_TRACK_MAX);
PID defendHorizontalPID(HORIZONTAL_P, I, HORIZONTAL_D, HORIZONTAL_MAX);
PID defendVerticalPID(VERTICAL_P, I, VERTICAL_D, VERTICAL_MAX);

void Defender::init() {
    timer = millis();
}

void Defender::update(const LSData& lsData, const CameraData& cameraData, const OrbitData& orbitData, float heading, float compassRot) { 
    movementValues[2] = cameraData.defendGoal ? -defendGoalPID.update(normaliseAngle(cameraData.defendGoalAngle), 180.0f) : compassRot;
    bool surge = cameraData.ball && (cameraData.ballDist < DEFEND_BALL_DISTANCE) && (cameraData.defendGoalDist < DEFEND_SURGE_DISTANCE) && (angleDiff(cameraData.ballAngle, 0.0f) < DEFEND_SURGE_ANGLE);
    if ((cameraData.ball && (angleDiff(cameraData.ballAngle, 0.0f) > DEFEND_ORBIT_ANGLE)) || surge) {
        movementValues[0] = surge ? DEFEND_SURGE_SPEED : orbitData.orbitSpeed;
        movementValues[1] = orbitData.orbitAngle;
        // if (surge) {
        //     movementValues[2] = compassRot;
        // }
    } else {
        float horizontalSpeed = cameraData.ball ? -defendHorizontalPID.update(normaliseHalfAngle(cameraData.ballAngle), 0.0f) : 0.0f;
        float verticalSpeed = cameraData.defendGoal ? defendVerticalPID.update(cameraData.defendGoalDist, DEFEND_GOAL_DISTANCE) : -25.0f;
        movementValues[0] = sqrtf(horizontalSpeed * horizontalSpeed + verticalSpeed * verticalSpeed);
        movementValues[1] = atan2f(horizontalSpeed, verticalSpeed) * RAD_TO_DEG_F;
    }
}