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
    long int countSteps = 0;
    long int countAxis = 0;

    bool b_direction = true;

    /*
    Stepper engine_1 = Stepper(26, 28, 30, 32);
    Stepper engine_2 = Stepper(27, 29, 31, 33);
    bool b_canNextStep = true;
    
    Timer timer = Timer(10, [] {
        b_canNextStep = true;
    });

    void Init() {
        engine_1.INIT();
        engine_2.INIT();
        // engine_1.setMaxSpeed(SPEED); // Устанавливаем скорость вращения об./мин.

        // engines.addStepper(engine_1);
        // engines.addStepper(engine_2);
    }

    void Move() {
        timer.Update();
        Serial.println(b_canNextStep);
        if (b_canNextStep) {
            engine_1.Move();
            engine_2.Move();
            b_canNextStep = false;
            countSteps++;
            countAxis = countSteps / 200;

            timer.Reset();
        }   
    }
    
    void Update() {
        // timer.Update();
        Move();
        // Serial.println("COIL!");
    }
    */
    
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
        
        engine_1.setSpeed(SSPEED * (b_direction ? -1 : 1));
        engine_2.setSpeed(SSPEED * (b_direction ? 1 : -1));

        engine_1.runSpeed();
        engine_2.runSpeed();
    }
    
    void Update() {
        // timer.Update();
        Move();
        // Serial.println("COIL!");
    }
};

#endif
