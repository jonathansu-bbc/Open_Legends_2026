#include <Adafruit_BNO055.h>
#include <attacker.h>
#include <bluetooth.h>
#include <camera.h>
#include <common.h>
#include <defender.h>
#include <lightSensors.h>
#include <motors.h>
#include <orbit.h>

Attacker attacker;
Bluetooth bluetooth;
Camera camera;
Defender defender;
Motors motors;
Orbit orbit;
LightSensors lightSensors;

Adafruit_BNO055 bno = Adafruit_BNO055(55, BNO055_ADDRESS_B, &Wire);
PID compassPID(COMPASS_P, INTEGRAL, COMPASS_D, COMPASS_MAX);

// unsigned long loopTime;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    camera.init();
    motors.init();
    lightSensors.init(); 
    // attacker.init();
    // defender.init();
    // bluetooth.init(); // decide initial role in setup
    Wire.begin();
    while (!bno.begin(OPERATION_MODE_IMUPLUS)) { 
        Serial.println("BNO not working");
        delay(1000);
    }
    delay(500);
    bno.setExtCrystalUse(true);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    // loopTime = millis();
}

void loop() {
    camera.read(); // account for heading?
    sensors_event_t compass;
    bno.getEvent(&compass);
    float heading = compass.orientation.x;
    float compassRot = compassPID.update(normaliseHalfAngle(heading), 0.0f);
    orbit.update(camera.cameraData); // account for heading?
    lightSensors.update(camera.cameraData, heading); // stopOnLine account for heading?
    
    bool attack = true; // BLUETOOTH

    if (attack) { // Attacker
        attacker.update(lightSensors.lsData, camera.cameraData, orbit.orbitData, compassRot);
        motors.move(attacker.movementValues[0], attacker.movementValues[1], attacker.movementValues[2]);
    } else { // Defender
        defender.update(lightSensors.lsData, camera.cameraData, orbit.orbitData, heading, compassRot);
        motors.move(defender.movementValues[0], defender.movementValues[1], defender.movementValues[2]);
    }
    // Serial.println(1000.0f / (float)(millis() - loopTime)); // loops/second
    // loopTime = millis();
}