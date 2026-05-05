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
#include <motor.h>
#include <motors.h>
// #include <orbit.h>
#include <PID.h>

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

Adafruit_BNO055 bno = Adafruit_BNO055(55, BNO055_ADDRESS_B, &Wire2);
PID compassPID(COMPASS_P, I, COMPASS_D, COMPASS_MAX);

// unsigned long loopTime;

void setup() {
    Serial.begin(9600);
    delay(2000);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    pinMode(FL_INA, OUTPUT);
    pinMode(FL_INB, OUTPUT);
    pinMode(FL_PWM, OUTPUT);

    pinMode(FR_INA, OUTPUT);
    pinMode(FR_INB, OUTPUT);
    pinMode(FR_PWM, OUTPUT);

    pinMode(BL_INA, OUTPUT);
    pinMode(BL_INB, OUTPUT);
    pinMode(BL_PWM, OUTPUT);

    pinMode(BR_INA, OUTPUT);
    pinMode(BR_INB, OUTPUT);
    pinMode(BR_PWM, OUTPUT);

    digitalWrite(FL_INA, LOW);
    digitalWrite(FL_INB, LOW);
    analogWrite(FL_PWM, 0);

    digitalWrite(FR_INA, LOW);
    digitalWrite(FR_INB, LOW);
    analogWrite(FR_PWM, 0);

    digitalWrite(BL_INA, LOW);
    digitalWrite(BL_INB, LOW);
    analogWrite(BL_PWM, 0);

    digitalWrite(BR_INA, LOW);
    digitalWrite(BR_INB, HIGH);
    analogWrite(BR_PWM, 255);

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
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(500);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(500);
    digitalWrite(BR_INA, LOW);
    digitalWrite(BR_INB, HIGH);
    analogWrite(BR_PWM, 255);
}