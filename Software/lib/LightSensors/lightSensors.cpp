#include "lightSensors.h"

void LightSensors::init() {
    for (uint8_t i = 0; i < 2; i++) {
        pinMode(lightOutPins[i], INPUT);
    } 
    for (uint8_t i = 0; i < 4; i++) {
        pinMode(lightPins[i], OUTPUT);
    }    
    read();
    for (uint8_t i = 0; i < LS_NUMBER; i++) {
        if (ROBOT_1) {
            whiteValues[i] = (i == 17) ? 900 : 825;
        } else if (ROBOT_2) {
            whiteValues[i] = lightValues[i] + 325;
        } else {
            whiteValues[i] = lightValues[i] + 200;
        }
    }
}

void LightSensors::read() {
    for (uint8_t channel = 0; channel < 32; channel++) {
        uint8_t muxInput = lightPinsIndex[channel];
        for (uint8_t j = 0; j < 4; j++) {
            digitalWrite(lightPins[j], (muxInput >> j) & 0x01);
        }
        delayMicroseconds(10);
        lightValues[channel] = analogRead((muxInput >= 16) ? LS_OUT_2 : LS_OUT);
        // Serial.print(lightValues[channel]);
        // Serial.print(" ");
    }
    // Serial.println();
}

float LightSensors::lineAngle() {
    for (uint8_t i = 0; i < 4; i++) {
        clusters[i][0] = 0;
        clusters[i][1] = 0;
        clusterAngles[i] = 0.0f;
        angleBetweenClusters[i] = 0;
    }
    line = false;
    for (uint8_t i = 0; i < LS_NUMBER; i++) {
        seesLine[i] = lightValues[i] >= whiteValues[i];
        line |= seesLine[i];
        // Serial.print(seesLine[i]);
        // Serial.print(" ");        
    }
    // Serial.println();
    for (uint8_t i = 0; i < LS_NUMBER; i++) { // Fills in faulty phototransistors
        uint8_t before = (i + 31) % 32;
        uint8_t after = (i + 1) % 32;
        if (seesLine[before] && !seesLine[i] && seesLine[after]) { // 0 surrounded by 1
            seesLine[i] = 1;
        }
        // else if (!seesLine[before] && seesLine[i] && !seesLine[after]) { // 1 surrounded by 0 (shouldn't happen because of thresholds)
        //     seesLine[i] = 0;
        // }
    }
    clusterStart = false;
    uint8_t cluster = 0;
    for (uint8_t i = 0; i < LS_NUMBER; i++) {
        if (seesLine[i]) {
            if (!clusterStart) { // Starts cluster
                clusters[cluster][0] = i;
                cluster += (i == 31) ? 1 : 0; // cluster++ if i == 31 is the start of a cluster
                clusterStart = true;
            } else if (i == 31) { // Ends cluster
                clusters[cluster][1] = i;
                cluster++;
                clusterStart = false;
            }
        } else {
            if (clusterStart) { // Ends cluster
                clusters[cluster][1] = i - 1;
                cluster++;
                clusterStart = false;
            }
        }
    }
    if (seesLine[31] && seesLine[0]) { // Merge first and last clusters
        clusters[0][0] = clusters[cluster - 1][0];
        cluster--;
    }
    // Line Angle Calculations
    if (cluster == 0) { // No line
        whiteAngle = -1.0f;
    } else if (cluster == 1) { // 1 cluster
        whiteAngle = midAngleBetween(clusters[0][0], clusters[0][1]); // Midpoint of cluster
    } else if (cluster == 2) { // 2 clusters
        clusterAngles[0] = midAngleBetween(clusters[0][0], clusters[0][1]); // Midpoint of cluster 0
        clusterAngles[1] = midAngleBetween(clusters[1][0], clusters[1][1]); // Midpoint of cluster 1
        whiteAngle = smallMidAngleBetween(clusterAngles[0], clusterAngles[1]); // Midpoint of minor arc between clusters 0 and 1
    } else if (cluster == 3) { // 3 clusters
        for (uint8_t i = 0; i < 3; i++) {
            clusterAngles[i] = midAngleBetween(clusters[i][0], clusters[i][1]); // Midpoint of clusters
        }
        for (uint8_t i = 0; i < 3; i++) {
            angleBetweenClusters[i] = (uint8_t)(round(angleDiff(clusterAngles[i], clusterAngles[(i + 1) % 3]))); // Smallest angle between clusters
        }
        uint8_t largestAngle = (uint8_t)max(max(angleBetweenClusters[0], angleBetweenClusters[1]), angleBetweenClusters[2]); // Largest angle between clusters
        for (uint8_t i = 0; i < 3; i++) {
            if (angleBetweenClusters[i] == largestAngle) { // whiteAngle midpoint of clusters furthest from each other, on the side of the remaining cluster
                whiteAngle = smallMidAngleBetween(clusterAngles[i], clusterAngles[(i + 1) % 3]); // Midpoint of minor arc between clusters
                if (angleDiff(whiteAngle, clusterAngles[(i + 2) % 3]) > 90.0f) { // Wrong side lol
                    whiteAngle = normaliseAngle(whiteAngle + 180.0f); // Flips whiteAngle
                }
                break;
            }
        }
    }
    // for (uint8_t i = 0; i < cluster; i++) {
    //     Serial.print(clusters[i][0]); Serial.print(" ");
    //     Serial.print(clusters[i][1]); Serial.print(" ");
    // }
    // Serial.print("   ");
    // Serial.printf("ClusterNo: %d\tWhiteAngle: %.1f", cluster, whiteAngle);
    // Serial.println();
    return whiteAngle;
}

float LightSensors::direction(float heading) {
    read();
    lineAngle();
    float correctedAngle = normaliseAngle(whiteAngle + heading);
    // Serial.printf("Line: %d\tState: %d\tWhiteAngle: %.1f\tCorrectedAngle: %.1f\tLineAngle: %.1f\n", line, state, whiteAngle, correctedAngle, lineAngle);
    if (state == 1) { // State 1
        if (line) { // State 2
            state = 2;
            correctedLineAngle = correctedAngle;
        }
    } else if (state == 4) { // State 4
        if (line) {
            state = 3;
            correctedLineAngle = normaliseAngle(correctedAngle + 180.0f);
        }
    } else { // On line (State 2 or 3)
        if (line) {
            if (angleDiff(correctedLineAngle, correctedAngle) <= AVOID_ANGLE_FLIP) { // State 2 // INCREASE (90/120/135)
                state = 2;
                correctedLineAngle = correctedAngle;
            } else { // State 3
                state = 3;
                correctedLineAngle = normaliseAngle(correctedAngle + 180.0f);
            }
        } else {
            if (state == 2) {
                state = 1;
                correctedLineAngle = -1.0f;
            } else {
                state = 4;
            }
        }
    }
    avoidAngle = (state != 1) ? normaliseAngle(correctedLineAngle - heading + 180.0f) : -1.0f;
    return avoidAngle;
}

bool LightSensors::stopOnLine(float ballAngle) {
    if (state == 2) { // Can only stop in state 2
        if (angleDiff(ballAngle, whiteAngle) < 60.0f) {
            return true;
        } 
        else {
            return false;
        }
    } else {
        return false;
    }
}

void LightSensors::update(const CameraData& cameraData, float heading) {
    lsData.avoidAngle = direction(heading);
    lsData.stopOnLine = stopOnLine(cameraData.ballAngle);
}