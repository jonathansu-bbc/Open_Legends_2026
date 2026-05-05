#ifndef ORBIT_H
#define ORBIT_H

#include "common.h"

class Orbit {
    public:
        Orbit() {};
        OrbitData orbitData;
        void update(const CameraData& cameraData);

    private:
        float speed(bool attackGoal, float attackGoalAngle, float ballAngle, float ballDist);
        float angle(bool attackGoal, float attackGoalAngle, float ballAngle, float ballDist);
        float moveSpeed = -1.0f;
};

#endif