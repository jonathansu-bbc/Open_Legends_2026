#ifndef ORBIT_H
#define ORBIT_H

#include "common.h"

class Orbit {
    public:
        Orbit() {};
        OrbitData orbitData;
        void update(const CameraData& cameraData);

    private:
        float velocity(bool attackGoal, float attackGoalAngle, float ballAngle, float ballDist);
        float direction(bool attackGoal, float attackGoalAngle, float ballAngle, float ballDist);
};

#endif