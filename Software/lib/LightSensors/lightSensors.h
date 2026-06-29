#ifndef LS_H
#define LS_H

#include "config.h"
#include "definitions.h"

class LightSensors {
    public:
        LightSensors() {};
        LSData lsData;
        void init();
        void read();
        float lineAngle();
        float direction(float heading);
        bool stopOnLine(bool ball, float ballAngle);
        void update(const CameraData& cameraData, float heading);

    private:
        uint8_t lightPins[4] = {LS_3, LS_2, LS_1, LS_0}; // Reversed on multiplexer schematic
        uint8_t lightOutPins[2] = {LS_OUT, LS_OUT_2};
        uint8_t lightPinsIndex[LS_NUMBER] = {7, 6, 5, 4, 3, 2, 1, 0, 24, 25, 26, 27, 28, 29, 30, 31, 23, 22, 21, 20, 19, 18, 17, 16, 8, 9, 10, 11, 12, 13, 14, 15};  
        uint8_t seesLine[LS_NUMBER] = {0};
        uint8_t clusters[4][2] = {{0}};
        uint8_t angleBetweenClusters[4] = {0};
        uint8_t state = 1;
        uint16_t lightValues[LS_NUMBER] = {0};
        uint16_t whiteValues[LS_NUMBER] = {0}; 
        float clusterAngles[4] = {0.0f};
        float whiteAngle = -1.0f;
        float avoidAngle = -1.0f;
        float correctedLineAngle = -1.0f;
        bool clusterStart;
        bool line;
};

#endif