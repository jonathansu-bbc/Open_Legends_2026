#ifndef DEFENDER_H
#define DEFENDER_H

#include "definitions.h"
#include "PID.h"

class Defender {
    public:
        Defender() {}
        void init();
        void update(const LSData& lsData, const CameraData& cameraData, const OrbitData& orbitData, float heading, float compassRot);
        float movementValues[3] = {0.0f};

    private:
        unsigned long timer;
};

#endif