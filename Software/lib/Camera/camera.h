#ifndef CAMERA_H
#define CAMERA_H

#include "config.h"
#include "definitions.h"

class Camera {
    public:
        Camera() {}
        CameraData cameraData;
        void init();
        void update(); 
        float fps;
        
    private:
        uint8_t camPins[2] = {CAMERA_TX, CAMERA_RX};  
        uint8_t camData[6] = {0};
        float distance(uint8_t cx, uint8_t cy);
        float angle(uint8_t cx, uint8_t cy);  
        unsigned long camTime = 0;
};

#endif