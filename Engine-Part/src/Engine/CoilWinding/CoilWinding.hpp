#ifndef _COILWINDING_H_
#define _COILWINDING_H_

#include "Libraries/AccelStepper/src/AccelStepper.h"
#include "Libraries/AccelStepper/src/MultiStepper.h"

#define ENA 7 // Пин первой обмотки
#define ENB 2 // Пин второй обмотки

#define COOLER_PIN 9

#define STEPS 200 // Количество шагов на один оборот
#define MSPEED 300 // Масимальная скорость
#define SSPEED 300 // Базовая скорость

/// Намотка катушки
namespace CoilWinding {
    /// Педаль
    static Pedal pedal = Pedal();

    /// Обдув
    static CoolerPWM cooler = {COOLER_PIN};

    /// Скорость вращения
    static float VSpeed = 1.0f; // [0; 1]
    /// Предыдущее кол-во оборотов
    double last_countTurn = 0.0f;

    /// Шаговый двигатель
    AccelStepper stepperMotor(AccelStepper::FULL4WIRE, 6, 5, 4, 3);
    /// Для вращения двигателей
    long positions[1] = { STEPS };

    /// Установить скорость вращения
    void SetSpeed(int speed);

    /// Создание
    void Init() {
        pinMode(PEDAL_PIN, INPUT);

        pinMode(ENA, OUTPUT);
        pinMode(ENB, OUTPUT);
        pinMode(COOLER_PIN, OUTPUT);

        stepperMotor.setCurrentPosition(Data::dataContainer.currentPosition);
        SetSpeed(Data::dataContainer.speed);
    }

    /// Установить скорость вращения
    void SetSpeed(int speed) {
        stepperMotor.setMaxSpeed(speed); // Устанавливаем скорость вращения об./мин.
        stepperMotor.setSpeed(-speed); // Устанавливаем скорость вращения об./мин.
    }

    /// Установить блок катушек
    void SetBlock(bool value) {
        digitalWrite(ENA, value);
        digitalWrite(ENB, value);
    }

    /// Перемещение
    void Move() {
        // степенная функция
        VSpeed = map(pow(pedal.currentValue, 5/4), 0, PEDAL_MAX - PEDAL_MIN, 0, 255) / 255.0f;
        //VSpeed = 0.25f;

        if (VSpeed != 0) {
            Data::dataContainer.countTurn = double(-stepperMotor.currentPosition()) / double(STEPS);
            Data::dataContainer.currentPosition = stepperMotor.currentPosition();

            if (Data::dataContainer.b_mode) {
                if (double(Data::dataContainer.limit_countTurn) - (Data::dataContainer.b_direction ? 1 : -1) * (Data::dataContainer.b_mainDirection ? 1 : -1) * Data::dataContainer.countTurn < 0) {
                    SetBlock(false);
                    return;
                }
                // Закомментировать, если не нужно ограничить вращение нулем
                if (Data::dataContainer.countTurn < 0 && ((!Data::dataContainer.b_direction && Data::dataContainer.b_mainDirection) || (Data::dataContainer.b_direction && !Data::dataContainer.b_mainDirection))) {
                    SetBlock(false);
                    return;
                }
            }

            SetBlock(true);
            stepperMotor.setSpeed(Data::dataContainer.speed * (Data::dataContainer.b_direction ? -1 : 1) * (Data::dataContainer.b_mainDirection ? 1 : -1) * VSpeed);
            stepperMotor.runSpeed();
        } else {
            SetBlock(false);
        }
    }
    
    /// Обновление
    void Update() {
        if (Data::dataContainer.b_canMove) {
            pedal.Update();
            Move();
        } else {
            SetBlock(false);
        }
    }
};

#endif
