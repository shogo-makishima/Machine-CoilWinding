#ifndef _VARIABLES_H_
#define _VARIABLES_H_

// #include "EEPROM.h"

bool localCanMove = true;
bool localDirection = true;
bool localMode = true;
//float localCountAxis = 0;
long localCountAxis = 0;

byte wasLoad_CanMove = 0;
byte wasLoad_Direction = 0;
byte wasLoad_Mode = 0;
byte wasLoad_CountAxis = 0;

namespace VariableController {
    bool cacheDirection = true;
    bool cacheMode = true;
    bool cacheCanMove = true;

    void Awake() {
        if (wasLoad_CountAxis == 0) {
            Serial1.println("M20");
            wasLoad_CountAxis++;
        }

        if (wasLoad_CountAxis == 2 && wasLoad_CanMove == 0) {
            Serial1.println("M21");
            wasLoad_CanMove++;
        }

        if (wasLoad_CanMove == 2 && wasLoad_Mode == 0) {
            Serial1.println("M22");
            wasLoad_Mode++;
        }

        if (wasLoad_Mode == 2 && wasLoad_Direction == 0) {
            Serial1.println("M23");
            wasLoad_Direction++;
        }
    }

    void CheckVariable() {
        if (localCanMove != cacheCanMove) {
            Serial1.println((localCanMove) ? "M0" : "M1");
        }

        if (localDirection != cacheDirection) {
            Serial1.println((localDirection) ? "M3" : "M4");
        }

        if (localMode != cacheMode) {
            Serial.println(1);
            Serial1.println((localMode) ? "M7" : "M8");
        }

        cacheCanMove = localCanMove;
        cacheDirection = localDirection;
        cacheMode = localMode;
    }
}

#endif