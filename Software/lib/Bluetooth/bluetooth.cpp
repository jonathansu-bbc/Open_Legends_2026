#include "bluetooth.h"

void Bluetooth::init() {
    pinMode(bluetoothPins[0], INPUT);
    pinMode(bluetoothPins[1], OUTPUT);
    BLUETOOTH_SERIAL.begin(9600);
    sendTimer = millis();
    switchTimer = millis();
}

void Bluetooth::send(float ballAngle, float ballDist) {
    thisData[0] = highByte((uint16_t)ballAngle);
    thisData[1] = lowByte((uint16_t)ballAngle);
    thisData[2] = (uint8_t)ballDist;
    thisData[3] = (uint8_t)attack;
    BLUETOOTH_SERIAL.write(BLUETOOTH_START_BYTE);
    BLUETOOTH_SERIAL.write(BLUETOOTH_START_BYTE);
    BLUETOOTH_SERIAL.write(thisData[0]);
    BLUETOOTH_SERIAL.write(thisData[1]);
    BLUETOOTH_SERIAL.write(thisData[2]);
    BLUETOOTH_SERIAL.write(thisData[3]);
}

void Bluetooth::read() {
    if (BLUETOOTH_SERIAL.available() >= BLUETOOTH_PACKET_NUMBER) { // full thingy
        uint8_t first = BLUETOOTH_SERIAL.read();
        uint8_t second = BLUETOOTH_SERIAL.peek();
        if (first == BLUETOOTH_START_BYTE && second == BLUETOOTH_START_BYTE) { // start byte
            BLUETOOTH_SERIAL.read();
            for (uint8_t byte = 0; byte < BLUETOOTH_PACKET_NUMBER - 2; byte++) {
                otherData[byte] = BLUETOOTH_SERIAL.read();
            }
        }
    }
}

void Bluetooth::role() {
    float thisBallAngle = float(((uint16_t)thisData[0] << 8) | thisData[1]);
    float thisBallDist = thisData[2];
    bool thisRole = thisData[3];
    float otherBallAngle = float(((uint16_t)otherData[0] << 8) | otherData[1]);
    float otherBallDist = otherData[2];
    bool otherRole = otherData[3];
    // Checks if defender good angle and distance
    if (thisRole == 0 && otherRole == 1) {
        if (angleDiff(thisBallAngle, 0.0f) < DEFEND_ORBIT_ANGLE && thisBallDist < DEFEND_BALL_DISTANCE) { // surge
            switching = true;
        } else {
            switching = false;
        }
    } else if (thisRole == 0 && otherRole == 1) {
        if (angleDiff(otherBallAngle, 0.0f) < DEFEND_ORBIT_ANGLE && otherBallDist < DEFEND_BALL_DISTANCE) { // surge
            switching = true;
        } else {
            switching = false;
        }
    } else {
        thisRole = thisBallDist < otherBallDist ? 1 : 0;
        otherRole = otherBallDist < thisBallDist ? 1 : 0;
    }
}

void Bluetooth::update(bool ball, float ballAngle, float ballDist) {
    if (ball) {
        if (millis() - sendTimer > 20) {
            send(ballAngle, ballDist);
            sendTimer = millis();
        }
        read();
        role();
        // if (millis() - switchTimer >  && switching) {
        //     attack = !attack;
        // }
    }
}