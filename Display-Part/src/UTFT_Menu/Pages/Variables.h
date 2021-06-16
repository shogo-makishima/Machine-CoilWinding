#ifndef _VARIABLES_H_
#define _VARIABLES_H_

// #include "EEPROM.h"

#define LIMIT_LIST_LENGHT 5

bool localCanMove = true;
bool localDirection = true;
bool localMode = true;
long localCountTurn = 0;

float localLimit = 0.0f;
byte localLimitMenu[LIMIT_LIST_LENGHT] = { 0, 0, 0, 0, 0 };

byte wasLoad_CanMove = 0;
byte wasLoad_Direction = 0;
byte wasLoad_Mode = 0;
byte wasLoad_CountAxis = 0;
byte wasLoad_Limit = 0;

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

        if (wasLoad_Direction == 2 && wasLoad_Limit == 0) {
            Serial1.println("M24");
            wasLoad_Limit++;
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

    float LimitToFloat() {
        return localLimitMenu[0] * 1000 + localLimitMenu[1] * 100 + localLimitMenu[2] * 10 + localLimitMenu[3] * 1 + localLimitMenu[4] / 10.0f;
    }

    void LimitFromFloat(float value) {
        int temp_limit = value * 10;
            
        for (int i = 0; i < LIMIT_LIST_LENGHT; i++) {
            int temp_dec = temp_limit / pow(10, LIMIT_LIST_LENGHT - (i + 1));
            localLimitMenu[i] = temp_dec;
            temp_limit -= temp_dec * pow(10, LIMIT_LIST_LENGHT - (i + 1));
        }

        localLimit = LimitToFloat();
    }

    void ClearLimit() {
        for (int i = 0; i < LIMIT_LIST_LENGHT; i++) localLimitMenu[i] = 0;
    }
}

#endif