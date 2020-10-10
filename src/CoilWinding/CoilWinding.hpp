#ifndef _COILWINDING_H_
#define _COILWINDING_H_

// #include "Libraries/AccelStepper/src/AccelStepper.h"
// #include "Libraries/AccelStepper/src/MultiStepper.h"
#include "Libraries/CustomStepper/CustomStepper.hpp"
#include "UTFT_Menu/Utilites/Timer.h"

#define STEPS 200 // Количество шагов на один оборот
#define SSPEED 200
#define PAUSE 10

namespace CoilWinding {
    Stepper engine_1 = Stepper(26, 28, 30, 32);
    Stepper engine_2 = Stepper(27, 29, 31, 33);
    bool b_canNextStep = true;
    long int countSteps = 0;
    long int countAxis = 0;
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

    /*
    AccelStepper engine_1(AccelStepper::FULL4WIRE, 26, 28, 30, 32);
    AccelStepper engine_2(AccelStepper::FULL4WIRE, 27, 29, 31, 33);
    long positions[2] = { STEPS, STEPS };
    MultiStepper engines;

    void Init() {
        engine_1.setMaxSpeed(SPEED); // Устанавливаем скорость вращения об./мин.
        engine_2.setMaxSpeed(SPEED); // Устанавливаем скорость вращения об./мин.

        engines.addStepper(engine_1);
        engines.addStepper(engine_2);
    }

    void Move() {
        engine_1.move(STEPS);
    }

    Timer timer = Timer(PAUSE, [] {
        Move();
    });
    
    void Update() {
        // timer.Update();
        Move();
        // Serial.println("COIL!");
    }
    */
};

#endif
