#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include <math.h>

/* Attack */
#define ATTACK_SLOW_SPEED 0.0f
#define ATTACK_FAST_SPEED 0.0f
#define ATTACK_CLOSE_DISTANCE 0.0f
#define ATTACK_FAR_DISTANCE 0.0f
#define ATTACK_SURGE_ANGLE 0.0f
#define ATTACK_SURGE_SPEED 0.0f
#define ORBIT_MAX_OFFSET 90.0f
#define ORBIT_MIN_MULTIPLIER 0.1f
#define ORBIT_MAX_MULTIPLIER 1.0f

/* Defend */
#define DEFEND_SURGE_SPEED 0.0f
#define DEFEND_GOAL_DISTANCE 0.0f
#define DEFEND_SURGE_DISTANCE 0.0f
#define DEFEND_BALL_DISTANCE 0.0f
#define DEFEND_SURGE_ANGLE 0.0f // 30.0f in 2025
#define DEFEND_ORBIT_ANGLE 0.0f

/* Out Avoidance */
#define AVOID_SPEED 0.0f
#define AVOID_ANGLE_STOP 0.0f // 60.0f in 2025
#define AVOID_ANGLE_FLIP 0.0f // 90.0f, 120.0f, 135.0f

/* PIDs */
// Compass Correct PID
#define IMU_KP (ROBOT_1 ? -0.5f : 0.0f)
#define IMU_KI (ROBOT_1 ? 0.0f : 0.0f)
#define IMU_KD (ROBOT_1 ? 0.0f : 0.0f)
#define IMU_MAX (ROBOT_1 ? 0.0f : 0.0f)

// Attacker Goal Tracking PID
#define ATTACK_GOAL_TRACK_KP (ROBOT_1 ? 0.5f : 0.0f) // High P
#define ATTACK_GOAL_TRACK_KI (ROBOT_1 ? 0.0f : 0.0f)
#define ATTACK_GOAL_TRACK_KD (ROBOT_1 ? 0.025f : 0.0f) // No D?
#define ATTACK_GOAL_TRACK_MAX (ROBOT_1 ? 25.0f : 0.0f)

// Defender Goal Tracking PID
#define DEFEND_GOAL_TRACK_KP (ROBOT_1 ? 0.0f : 0.0f) // High P
#define DEFEND_GOAL_TRACK_KI (ROBOT_1 ? 0.0f : 0.0f)
#define DEFEND_GOAL_TRACK_KD (ROBOT_1 ? 0.0f : 0.0f) // High D
#define DEFEND_GOAL_TRACK_MAX (ROBOT_1 ? 0.0f : 0.0f)

// Horizontal PID
#define HORIZONTAL_KP (ROBOT_1 ? 0.0f : 0.0f)
#define HORIZONTAL_KI (ROBOT_1 ? 0.0f : 0.0f)
#define HORIZONTAL_KD (ROBOT_1 ? 0.0f : 0.0f) // No D
#define HORIZONTAL_MAX (ROBOT_1 ? 0.0f : 0.0f) // Lower absoluteMax if overshooting big differences

// Vertical PID
#define VERTICAL_KP (ROBOT_1 ? 0.0f : 0.0f)
#define VERTICAL_KI (ROBOT_1 ? 0.0f : 0.0f)
#define VERTICAL_KD (ROBOT_1 ? 0.0f : 0.0f) // No D
#define VERTICAL_MAX (ROBOT_1 ? 0.0f : 0.0f) // Lower absoluteMax if overshooting big differences

/* Pins */
// Motors
#define MOTOR_NUM 4
#define MOTOR_PWM_FREQ 15000.0f

#define MOTOR_KP 0.005f
#define MOTOR_KI 0.0f
#define MOTOR_KD 0.0f
#define MOTOR_ABS_MAX 0.25f

#define FL_PWM 29
#define FL_INA 32
#define FL_INB 31

#define FR_PWM 12
#define FR_INA 28
#define FR_INB 27

#define BR_PWM 6
#define BR_INA 8
#define BR_INB 7

#define BL_PWM 9
#define BL_INA 11
#define BL_INB 10

// Light Sensors
#define LS_NUMBER 32
#define LS_0 37
#define LS_1 36
#define LS_2 35
#define LS_3 34
#define LS_OUT 40
#define LS_OUT_2 39
#define LS_OUT_3 38

// Camera
#define CAMERA_SERIAL Serial1
#define CAMERA_PACKET_NUMBER 8
#define CAMERA_START_BYTE 255
#define CAMERA_TX 0
#define CAMERA_RX 1

// Bluetooth
#define BLUETOOTH_SERIAL Serial5
#define BLUETOOTH_PACKET_NUMBER 6
#define BLUETOOTH_START_BYTE 255
#define BLUETOOTH_TX 21
#define BLUETOOTH_RX 20

// LRFs
// #define X_SHUT_LRF_1 (ROBOT_1 ? 26 : 37)
// #define X_SHUT_LRF_2 (ROBOT_1 ? 27 : 41)
// #define X_SHUT_LRF_3 (ROBOT_1 ? 20 : 2)
// #define X_SHUT_LRF_4 (ROBOT_1 ? 40 : 30)

// Function Declarations
float normaliseHalfAngle(float angle);
float normaliseAngle(float angle);
float angleDiff(float angle_1, float angle_2);
float midAngle(uint8_t index_1, uint8_t index_2);
float smallMidAngle(float angle_1, float angle_2);
float ballCamToDist(float ballPixelDistance);
float goalCamToDist(float goalPixelDistance);

/* Trigonometry */
#define RAD_TO_DEG_F 57.29578f
#define DEG_TO_RAD_F 0.017453293f

/* Structs */
struct LSData {
    bool stopOnLine;
    float lineAngle;
    float avoidSpeed;
    float avoidAngle;
};

struct CameraData {
    bool newData;
    bool ball;
    bool attackGoal;
    bool defendGoal;
    float ballAngle;
    float ballDist;
    float attackGoalAngle;
    float attackGoalDist;
    float defendGoalAngle;
    float defendGoalDist;
};

struct OrbitData {
    float orbitSpeed;
    float orbitAngle;
};

// struct BluetoothData {
//
// };

#endif