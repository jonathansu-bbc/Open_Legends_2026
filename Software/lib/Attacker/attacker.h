#ifndef ATTACKER_H
#define ATTACKER_H

#include "common.h"
#include "PID.h"

class Attacker {
    public:
        Attacker() {}
        void init();
        void update(const LSData& lsData, const CameraData& cameraData, const OrbitData& orbitData, float compassRot);
        float movementValues[3] = {0};

    private:
        unsigned long timer;
};

#endif