#ifndef _COILWINDING_H_
#define _COILWINDING_H_

#include "Libraries/AccelStepper/src/AccelStepper.h"
#include "Libraries/AccelStepper/src/MultiStepper.h"
// #include "Libraries/CustomStepper/CustomStepper.hpp"
#include "UTFT_Menu/Utilites/Timer.h"

#define STEPS 200 // Количество шагов на один оборот
#define MSPEED 300
#define SSPEED 300
#define SACELERATION 300
#define PAUSE 25

namespace CoilWinding {
    static bool VCanMove = true;

    static float VSpeed = 1.0f; // [0; 1]
    static bool VFirstLoad = true;
    static long int VMaxINT = 0; // size = 4 byte

    static int VMax[6] = { 0, 0, 0, 0, 0, 0, };

    void EnterVSpeedInt() {
        Serial.println("[VSPEED] { " + String(VMax[0]) + ", " + String(VMax[1]) + ", ... }");
        VMaxINT = VMax[0] * 100000 + VMax[1] * 10000 + VMax[2] * 1000 + VMax[3] * 100 + VMax[4] * 10 + VMax[5] * 1; 
        Serial.println("[SPEED] " + String(VMaxINT));
    }

    void ClearVSpeed() {
        for (int i = 0; i < 6; i++) VMax[i] = 0;
    }

    void LoadVSpeedInt() {
        Serial.println("[LOAD] VSpeed");
        // eeprom_read_block((void*)&VSpeed, (const void*)&VSpeed_ADDR, sizeof(VSpeed));
        EnterVSpeedInt();
    }

    void SaveVSpeedInt() {
        Serial.println("[SAVE] VSpeed");
        // eeprom_write_block((void*)&VSpeed, (const void*)&VSpeed_ADDR, sizeof(VSpeed));
    }


    long int countSteps = 0;
    long int countAxis = 0;

    bool b_direction = true;


    long int maxSteps = 0;
    
    AccelStepper engine_1(AccelStepper::FULL4WIRE, 26, 28, 30, 32);
    AccelStepper engine_2(AccelStepper::FULL4WIRE, 27, 29, 31, 33);
    long positions[2] = { STEPS, STEPS };
    MultiStepper engines;

    void Init() {
        engine_1.setMaxSpeed(MSPEED); // Устанавливаем скорость вращения об./мин.
        engine_2.setMaxSpeed(MSPEED); // Устанавливаем скорость вращения об./мин.

        engine_1.setSpeed(-SSPEED); // Устанавливаем скорость вращения об./мин.
        engine_2.setSpeed(SSPEED); // Устанавливаем скорость вращения об./мин.
        
        engines.addStepper(engine_1);
        engines.addStepper(engine_2);
    }

    void Move() {
        countSteps += b_direction ? 1 : -1;
        countAxis = countSteps / STEPS;
        
        engine_1.setSpeed(SSPEED * (b_direction ? -1 : 1) * VSpeed);
        engine_2.setSpeed(SSPEED * (b_direction ? 1 : -1) * VSpeed);

        engine_1.runSpeed();
        engine_2.runSpeed();
    }
    
    void Update() {
        if (VCanMove) Move();
    }
};

#endif
