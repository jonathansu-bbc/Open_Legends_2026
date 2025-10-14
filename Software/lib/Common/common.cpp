#include "common.h"

float normaliseHalfAngle(float angle) { // Converts to (-180, 180] degrees
    angle = normaliseAngle(angle) - 180.0f;
    if (angle == -180.0f) {
        angle += 360.0f;
    }
    return angle;
}

float normaliseAngle(float angle) { // Converts to [0, 360) degrees
    angle = fmodf(angle, 360.0f);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

float angleDiff(float angle_1, float angle_2) { // Finds the smallest angle between two angles
    float angleBetween = fabs(angle_1 - angle_2);
    return fminf(angleBetween, 360.0f - angleBetween);
}

float midAngleBetween(uint8_t index_1, uint8_t index_2) { // Finds the middle angle of a cluster
    if (index_1 > index_2) {
        index_2 += 32;
    }
    float angle = 3.75f + 0.5f * float(index_1 + index_2) * 11.25f;
    return normaliseAngle(angle);
}

float smallMidAngleBetween(float angle_1, float angle_2) { // Finds the angle between two angles on the side of the two angles
    float diff = angle_2 - angle_1;
    if (diff > 180.0f) {
        diff -= 360.0f;
    } else if (diff < -180.0f) {
        diff += 360.0f;
    }
    return normaliseAngle(angle_1 + diff / 2.0f);
}

float ballCamToDist(float pixelDistance) { // Converts ball pixel distance to centimetres
    return powf(1.0f, (pixelDistance - 1.0f)) + 1.0f; // tune
}

float goalCamToDist(float pixelDistance) {// Converts goal pixel distance to centimetres
    return powf(1.0f, (pixelDistance - 1.0f)) + 1.0f; // tune
}