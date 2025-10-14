#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "common.h"

class Bluetooth {
    public:
        Bluetooth() {}
        void init();
        void update(bool ball, float ballAngle, float ballDist);
        bool attack;

    private:
        uint8_t bluetoothPins[2] = {BLUETOOTH_TX, BLUETOOTH_RX};
        uint8_t thisData[4] = {0}; // high ballAngle, low ballAngle, ballDist, role
        uint8_t otherData[4] = {0}; // high ballAngle, low ballAngle, ballDist, role
        void read();
        void send(float ballAngle, float ballDist);
        void role();
        bool switching;
        unsigned long sendTimer;
        unsigned long switchTimer;

};

#endif