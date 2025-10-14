#include "camera.h"

void Camera::init() {
    pinMode(camPins[0], INPUT);
    pinMode(camPins[1], OUTPUT);
    CAMERA_SERIAL.begin(115200);
}

void Camera::read() {
    bool yellowGoal = false;
    bool blueGoal = false;
    if (CAMERA_SERIAL.available() >= CAMERA_PACKET_NUMBER) { // Full packet
        uint8_t first = CAMERA_SERIAL.read();
        uint8_t second = CAMERA_SERIAL.peek();
        if (first == CAMERA_START_BYTE && second == CAMERA_START_BYTE) { // Start byte
            CAMERA_SERIAL.read();
            for (uint8_t byte = 0; byte < CAMERA_PACKET_NUMBER - 2; byte++) {
                camData[byte] = CAMERA_SERIAL.read();
            }
            cameraData.ball = camData[0] != 120 || camData[1] != 120;
            yellowGoal = camData[2] != 120 || camData[3] != 120;
            blueGoal = camData[4] != 120 || camData[5] != 120;
            // Serial.println(1000.0f / (float)(millis() - camTime));
            // camTime = millis();
        }
    }
    cameraData.ballDist = distance(camData[0], camData[1]);
    cameraData.ballAngle = angle(camData[0], camData[1]);
    float yellowGoalDist = distance(camData[2], camData[3]);
    float yellowGoalAngle = angle(camData[2], camData[3]);
    float blueGoalDist = distance(camData[4], camData[5]);
    float blueGoalAngle = angle(camData[4], camData[5]);
    cameraData.attackGoal = BLUE_GOAL_ATTACK ? blueGoal : yellowGoal;
    cameraData.defendGoal = BLUE_GOAL_ATTACK ? yellowGoal : blueGoal;
    cameraData.attackGoalDist = BLUE_GOAL_ATTACK ? blueGoalDist : yellowGoalDist;
    cameraData.defendGoalDist = BLUE_GOAL_ATTACK ? yellowGoalDist : blueGoalDist;
    cameraData.attackGoalAngle = BLUE_GOAL_ATTACK ? blueGoalAngle : yellowGoalAngle;
    cameraData.defendGoalAngle = BLUE_GOAL_ATTACK ? yellowGoalAngle : blueGoalAngle;
}

float Camera::distance(uint8_t cx, uint8_t cy) {
    int8_t y = 120 - cy;
    int8_t x = 120 - cx;
    return sqrtf((float)(x*x + y*y));
}

float Camera::angle(uint8_t cx, uint8_t cy) {
    int8_t y = 120 - cy;
    int8_t x = 120 - cx;
    float angle = 450.0f - RAD_TO_DEG_F * atan2f((float)y, (float)x);
    if (angle >= 360.0f) {
        return angle - 360.0f;
    }
    return angle;
}