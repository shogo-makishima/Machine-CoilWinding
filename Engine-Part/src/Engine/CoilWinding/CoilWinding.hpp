#ifndef _COILWINDING_H_
#define _COILWINDING_H_

#include "Libraries/AccelStepper/src/AccelStepper.h"
#include "Libraries/AccelStepper/src/MultiStepper.h"

#define COOLER_PIN 9

#define STEPS 200 // Количество шагов на один оборот
#define MSPEED 300 // Масимальная скорость
#define SSPEED 300 // Базовая скорость
#define SSCALE 2

/// Намотка катушки
namespace CoilWinding {
    /// Педаль
    static Pedal pedal = Pedal();

    /// Обдув
    static CoolerPWM cooler = {COOLER_PIN};

    /// Скорость вращения
    static float VSpeed = 1.0f; // [0; 1]
    /// Предыдущее кол-во оборотов
    double last_countTurn = -999.0f;

    /// Шаговый двигатель
    AccelStepper stepperMotor(1, 4, 3);
    /// Для вращения двигателей
    long positions[1] = { STEPS };

    /// Установить скорость вращения
    void SetSpeed(int speed);

    /// Создание
    void Init() {
        pinMode(PEDAL_PIN, INPUT);
        
        pinMode(2, OUTPUT);
        digitalWrite(2, HIGH);

        stepperMotor.setCurrentPosition(Data::dataContainer.currentPosition);
        // stepperMotor.setMaxSpeed(1000 * SSCALE);
        SetSpeed(Data::dataContainer.speed * SSCALE);
    }

    /// Установить скорость вращения
    void SetSpeed(int speed) {
        stepperMotor.setMaxSpeed(speed); // Устанавливаем скорость вращения об./мин.
        stepperMotor.setSpeed(speed); // Устанавливаем скорость вращения об./мин.
    }

    /// Перемещение
    void Move() {
        // степенная функция
        VSpeed = map(pedal.currentValue, 0, PEDAL_MAX - PEDAL_MIN, 0, 255) / 255.0f;
        //VSpeed = 0.25f;

        if (VSpeed != 0) {
            Data::dataContainer.countTurn = (double(-stepperMotor.currentPosition()) / double(STEPS)) / SSCALE;
            Data::dataContainer.currentPosition = stepperMotor.currentPosition();

            if (Data::dataContainer.b_mode) {
                if (double(Data::dataContainer.limit_countTurn) - (Data::dataContainer.b_direction ? 1 : -1) * (Data::dataContainer.b_mainDirection ? 1 : -1) * Data::dataContainer.countTurn < 0) {

                    return;
                }
                // Закомментировать, если не нужно ограничить вращение нулем
                if (Data::dataContainer.countTurn < 0 && ((!Data::dataContainer.b_direction && Data::dataContainer.b_mainDirection) || (Data::dataContainer.b_direction && !Data::dataContainer.b_mainDirection))) {

                    return;
                }
            }

            SetSpeed(Data::dataContainer.speed * SSCALE * (Data::dataContainer.b_direction ? -1 : 1) * (Data::dataContainer.b_mainDirection ? 1 : -1) * VSpeed);
            stepperMotor.runSpeed();
        } else {
        }
    }
    
    /// Обновление
    void Update() {
        if (Data::dataContainer.b_canMove && Data::b_isInit && !Data::b_isBlock) {
            pedal.Update();
            Move();
        } else {
        }
    }
};

#endif
