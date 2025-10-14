#ifndef DEFS_H
#define DEFS_H

#include <Arduino.h>
#include <math.h>
#include <Wire.h>

// Robot
#define ROBOT_1 false
#define ROBOT_2 false

// Attack Direction
#define BLUE_GOAL_ATTACK false
// True: Attacking Blue Goal (Defending Yellow Goal)
// False: Attacking Yellow Goal (Defending Blue Goal)

// Attack
#define ATTACK_SLOW_SPEED 0.0f
#define ATTACK_FAST_SPEED 0.0f
#define ATTACK_CLOSE_DISTANCE 0.0f
#define ATTACK_FAR_DISTANCE 0.0f
#define ATTACK_SURGE_ANGLE 0.0f
#define ATTACK_MIN_OFFSET 0.0f
#define ATTACK_MAX_OFFSET 0.0f
#define ATTACK_MIN_SPEED_SCALE_FACTOR 0.0f
#define ATTACK_MAX_SPEED_SCALE_FACTOR 0.0f
// #define ATTACK_MIN_SURGE_SPEED 0.0f
// #define ATTACK_MAX_SURGE_SPEED 0.0f
#define ATTACK_SURGE_SPEED 0.0f
#define ATTACK_MIN_ANGLE_SCALE_FACTOR 0.0f
#define ATTACK_MAX_ANGLE_SCALE_FACTOR 0.0f

// Defend
#define DEFEND_SURGE_SPEED 0.0f
#define DEFEND_GOAL_DISTANCE 0.0f
#define DEFEND_SURGE_DISTANCE 0.0f
#define DEFEND_BALL_DISTANCE 0.0f
#define DEFEND_ORBIT_ANGLE 0.0f

// Out Avoidance
#define AVOID_SPEED 0.0f
#define AVOID_ANGLE_FLIP 0.0f

// PIDs
// Overshooting big differences: lower absolute max
#define INTEGRAL 0.0f
// Compass Correct PID
#define COMPASS_P (ROBOT_1 ? 0.0f : 0.0f)
#define COMPASS_D (ROBOT_1 ? 0.0f : 0.0f)
#define COMPASS_MAX (ROBOT_1 ? 0.0f : 0.0f)

// Goal Tracking PID
#define GOAL_TRACK_P (ROBOT_1 ? 0.0f : 0.0f) // High P
#define GOAL_TRACK_D (ROBOT_1 ? 0.0f : 0.0f) // High D
#define ATTACK_GOAL_TRACK_MAX (ROBOT_1 ? 0.0f : 0.0f)
#define DEFEND_GOAL_TRACK_MAX (ROBOT_1 ? 0.0f : 0.0f)

// Horizontal PID
#define HORIZONTAL_P (ROBOT_1 ? 0.0f : ROBOT_2 ? 0.0f : 0.0f)
#define HORIZONTAL_D (ROBOT_1 ? 0.0f : ROBOT_2 ? 0.0f : 0.0f) // No D
#define HORIZONTAL_MAX (ROBOT_1 ? 0.0f : 0.0f)

// Vertical PID
#define VERTICAL_P (ROBOT_1 ? 0.0f : 0.0f)
#define VERTICAL_D (ROBOT_1 ? 0.0f : 0.0f) // No D
#define VERTICAL_MAX (ROBOT_1 ? 0.0f : 0.0f)

// Motor pins on Teensy
#define FL_PWM 0
#define FL_INA 0
#define FL_INB 0

#define FR_PWM 0
#define FR_INA 0
#define FR_INB 0

#define BR_PWM 0
#define BR_INA 0
#define BR_INB 0

#define BL_PWM 0
#define BL_INA 0
#define BL_INB 0

// Light Sensors
#define LS_NUMBER 32
#define LS_0 0
#define LS_1 0
#define LS_2 0
#define LS_3 0
#define LS_OUT 0
#define LS_OUT_2 0

// Camera
#define CAMERA_SERIAL Serial1
#define CAMERA_PACKET_NUMBER 8
#define CAMERA_START_BYTE 255
#define CAMERA_TX 0
#define CAMERA_RX 0

// Bluetooth
#define BLUETOOTH_SERIAL Serial6
#define BLUETOOTH_PACKET_NUMBER 6
#define BLUETOOTH_START_BYTE 255
#define BLUETOOTH_TX 0
#define BLUETOOTH_RX 0

// LRFs
// #define X_SHUT_LRF_1 (ROBOT_1 ? 26 : 37)
// #define X_SHUT_LRF_2 (ROBOT_1 ? 27 : 41)
// #define X_SHUT_LRF_3 (ROBOT_1 ? 20 : 2)
// #define X_SHUT_LRF_4 (ROBOT_1 ? 40 : 30)

// Function Declarations
float normaliseHalfAngle(float angle);
float normaliseAngle(float angle);
float angleDiff(float angle_1, float angle_2);
float midAngleBetween(uint8_t index_1, uint8_t index_2);
float smallMidAngleBetween(float angle_1, float angle_2);
float ballCamToDist(float pixelDistance);
float goalCamToDist(float pixelDistance);

// Trigonometry
#define RAD_TO_DEG_F 57.29578f
#define DEG_TO_RAD_F 0.017453293f

struct LSData {
    bool stopOnLine;
    float avoidAngle;
};

struct CameraData {
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
//     a
// };

#endif