#include <Adafruit_BNO055.h>
#include <bluetooth.h>
#include <camera.h>
// #include <definitions.h>
#include <config.h>
#include <dribbler.h>
#include <kicker.h>
#include <lightSensors.h>
#include <motor.h>
#include <motors.h>
#include <orbit.h>
#include <PID.h>

Bluetooth bluetooth;
Camera camera;
Dribbler dribbler;
Kicker kicker;
LightSensors lightSensors;
LSData lsdata;
Motors motors;
Orbit orbit;
OrbitData orbitdata;
// IntervalTimer motorsOnTimer;
IntervalTimer ledTimer;

Adafruit_BNO055 bno = Adafruit_BNO055(55, BNO055_ADDRESS_B, &Wire2);
PID imuPID(IMU_KP, IMU_KI, IMU_KD, IMU_MAX);
PID attackGoalTrackPID(ATTACK_GOAL_TRACK_KP, ATTACK_GOAL_TRACK_KI, ATTACK_GOAL_TRACK_KD, ATTACK_GOAL_TRACK_MAX);

// static volatile uint8_t motorsOn = 0;
static volatile uint8_t ledOn = 0;
static float attackGoalAngle = 0.0f; // in case first loop doesn't have camera values
static float attackGoalRot = 0.0f;

// void motorsOnUpdate() {
//     motorsOn = (motorsOn + 1) % 100;
// }

void toggleLED() {
    ledOn = 1 - ledOn;
    digitalWrite(LED_BUILTIN, ledOn);
}

void setup()
{
    delay(100);

    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    motors.init();
    camera.init();
    // lightSensors.init();
    // attacker.init();
    // defender.init();
    // bluetooth.init();
    // kicker and dribbler

    // while (!bno.begin(OPERATION_MODE_IMUPLUS)) { 
    //     Serial.println("BNO not working");
    //     delay(1000);
    // }
    // delay(500);
    // bno.setExtCrystalUse(true);
    // delay(500);

    digitalWrite(LED_BUILTIN, LOW);

    // motorsOnTimer.begin(motorsOnUpdate, 1000);
    ledTimer.begin(toggleLED, 500000);
}

void loop() {
    // sensors_event_t imu;
    // bno.getEvent(&imu);
    // float heading = imu.orientation.x;

    // if (heading > 180.0f) {
    //     heading -= 360.0f;
    // }

    // float compassRot = imuPID.update(heading, 0.0f);

    camera.update();
    if (camera.cameraData.newData) {
        attackGoalAngle = camera.cameraData.attackGoalAngle;
        if (attackGoalAngle > 180.0f) {
            attackGoalAngle -= 360.0f;
        }
        attackGoalRot = -attackGoalTrackPID.update(attackGoalAngle, 0.0f);
    }
    orbit.update(camera.cameraData);
    motors.move(orbit.orbitData.orbitSpeed, orbit.orbitData.orbitAngle, attackGoalRot);
    // motors.move(25.0f, 90.0f, 0.0f);
    
    // lightSensors.update(camera.cameraData, heading); // stopOnLine account for heading?
    // bool attack = true; // BLUETOOTH
    // if (attack) { // Attacker
    //     attacker.update(lightSensors.lsData, camera.cameraData, orbit.orbitData, heading, compassRot);
    //     motors.move(attacker.movementValues[0], attacker.movementValues[1], attacker.movementValues[2]);
    // } else { // Defender
    //     defender.update(lightSensors.lsData, camera.cameraData, orbit.orbitData, heading, compassRot);
    //     motors.move(defender.movementValues[0], defender.movementValues[1], defender.movementValues[2]);
    // }

    #if DEBUG_IMU
    Serial.printf("Heading: %.2f\tCorrection: %.2f\tMode: %d", heading, compassRot, (uint8_t)bno.getMode());
    #endif

    #if DEBUG_CAMERA
    Serial.printf("ballAngle: %.2f\tattackGoalAngle: %.2f\tdefendGoalAngle: %.2f\tFPS: %.2f", camera.cameraData.ballAngle, camera.cameraData.attackGoalAngle, camera.cameraData.defendGoalAngle. camera.fps);
    #endif

    #if DEBUG_GOAL_CORRECT
    Serial.printf("attackGoalAngle: %.2f\tattackGoalRot: %.2f", attackGoalAngle, attackGoalRot);
    #endif

    #if DEBUG
    Serial.println();
    #endif
}