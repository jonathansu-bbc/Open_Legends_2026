#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
// #include <attacker.h>
// #include <bluetooth.h>
// #include <camera.h>
#include <common.h>
// #include <defender.h>
// #include <dribbler.h>
// #include <kicker.h>
// #include <lightSensors.h>
// #include <motor.h>
#include <motors.h>
// #include <orbit.h>
// #include <PID.h>

// Attacker attacker;
// Bluetooth bluetooth;
// Camera camera;
// CameraData cameradata;
// Defender defender;
// Dribbler dribbler;
// Kicker kicker;
// LightSensors lightSensors;
// LSData lsdata;
Motors motors;
// Orbit orbit;
// OrbitData orbitdata;
IntervalTimer myTimer;

Adafruit_BNO055 bno = Adafruit_BNO055(55, BNO055_ADDRESS_B, &Wire2);
// PID compassPID(COMPASS_P, I, COMPASS_D, COMPASS_MAX);

// unsigned long loopTime;

float speed = 0;

// uint8_t ledon = 1;
static volatile uint8_t motorsOn = 0;

void interrupt() {
    motorsOn = (motorsOn + 1) % 50;
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    // digitalWrite(LED_BUILTIN, HIGH);
    motors.init();
    // camera.init();
    // motors.init();
    // lightSensors.init(); 
    // attacker.init();
    // defender.init();
    // bluetooth.init(); // decide initial role in setup
    // kicker and dribbler init where?
    // Wire2.begin();
    // while (!bno.begin(OPERATION_MODE_IMUPLUS)) { 
    //     Serial.println("BNO not working");
    //     delay(1000);
    // }
    // delay(500);
    // bno.setExtCrystalUse(true);
    // delay(500);
    // digitalWrite(LED_BUILTIN, LOW);
    // loopTime = millis();
    myTimer.begin(interrupt, 2000);
}

void loop() {
    // sensors_event_t compass;
    // bno.getEvent(&compass);
    // float heading = compass.orientation.x;
    // float compassRot = compassPID.update(normaliseHalfAngle(heading), 0.0f);
    // camera.update();
    // orbit.update(camera.cameraData);
    // lightSensors.update(camera.cameraData, heading); // stopOnLine account for heading?
    
    // bool attack = true; // BLUETOOTH

    // if (attack) { // Attacker
    //     attacker.update(lightSensors.lsData, camera.cameraData, orbit.orbitData, heading, compassRot);
    //     motors.move(attacker.movementValues[0], attacker.movementValues[1], attacker.movementValues[2]);
    // } else { // Defender
    //     defender.update(lightSensors.lsData, camera.cameraData, orbit.orbitData, heading, compassRot);
    //     motors.move(defender.movementValues[0], defender.movementValues[1], defender.movementValues[2]);
    // }
    // Serial.println(1000.0f / (float)(millis() - loopTime)); // loops/second
    // loopTime = millis();
    // motors.move(0.0f, 0.0f, -30.0f);

    if (motorsOn > 1) {
        motors.move(0.0f, 0.0f, -20.0f);
    } else {
        motors.move(0.0f, 0.0f, 0.0f);
    }

        // if (speed >= 250.0f) {
    //     speed = -250.0f;
    // }
    // speed += 10;
    // motors.move(0.0f, 0.0f, speed);
    // ledon ^= 1;
    // digitalWrite(LED_BUILTIN, ledon);
    // delay(100);
    // motors.move(0.0f, 0.0f, 0.0f);
    // ledon ^= 1;
    // digitalWrite(LED_BUILTIN, ledon);
    // delay(2);
}