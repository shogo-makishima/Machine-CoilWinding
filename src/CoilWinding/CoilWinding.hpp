#ifndef _COILWINDING_H_
#define _COILWINDING_H_

#include "Libraries/AccelStepper/src/AccelStepper.h"
#include "Libraries/AccelStepper/src/MultiStepper.h"
// #include "Libraries/CustomStepper/CustomStepper.hpp"
#include "UTFT_Menu/Utilites/Timer.h"

#define STEPS 200 // Количество шагов на один оборот
#define MSPEED 200 // Масимальная скорость
#define SSPEED 200 // Базовая скорость

/// Намотка катушки
namespace CoilWinding {
    /// Педаль
    static Pedal pedal = Pedal();

    /// Может вращаться
    static bool b_canMove = false;

    /// Скорость вращения
    static float VSpeed = 1.0f; // [0; 1]
    /// Первый ли запуск после включения питания
    static bool VFirstLoad = true;
    /// Максимальное кол-во оборотов INT
    static long int VMaxINT = 0; // size = 4 byte

    /// Максимальное кол-во оборотов ARRAY
    static int VMax[6] = { 0, 0, 0, 0, 0, 0, };

    /// Получить кол-во оборотов из массива
    void EnterVSpeedInt() {
        Serial.println("[VSPEED] { " + String(VMax[0]) + ", " + String(VMax[1]) + ", ... }");
        VMaxINT = VMax[0] * 100000 + VMax[1] * 10000 + VMax[2] * 1000 + VMax[3] * 100 + VMax[4] * 10 + VMax[5] * 1; 
        Serial.println("[SPEED] " + String(VMaxINT));
    }

    /// Очистить массив кол-ва оборотов
    void ClearVSpeed() {
        for (int i = 0; i < 6; i++) VMax[i] = 0;
    }

    /// Загрузить массив кол-ва оборотов
    void LoadVSpeedInt() {
        Serial.println("[LOAD] VSpeed");
        // eeprom_read_block((void*)&VSpeed, (const void*)&VSpeed_ADDR, sizeof(VSpeed));
        EnterVSpeedInt();
    }

    /// Сохранить массив кол-ва оборотов
    void SaveVSpeedInt() {
        Serial.println("[SAVE] VSpeed");
        // eeprom_write_block((void*)&VSpeed, (const void*)&VSpeed_ADDR, sizeof(VSpeed));
    }

    /// Кол-во шагов
    long int countSteps = 0;
    /// Кол-во оборотов
    long int countAxis = 0;

    /// Направление
    bool b_direction = true;

    /// Шаговый двигатель
    AccelStepper stepperMotor(AccelStepper::FULL4WIRE, 27, 29, 31, 33);
    /// Для вращения двигателей
    long positions[1] = { STEPS };

    /// Создание
    void Init() {
        stepperMotor.setMaxSpeed(MSPEED); // Устанавливаем скорость вращения об./мин.
        stepperMotor.setSpeed(-SSPEED); // Устанавливаем скорость вращения об./мин.
    }

    /// Перемещение
    void Move() {
        countSteps += b_direction ? 1 : -1;
        countAxis = countSteps / STEPS;
        
        /// степенная функция
        VSpeed = map(pow(pedal.currentValue, 5/4), 0, PEDAL_MAX - PEDAL_MIN, 0, 255) / 255.0f;
        // Serial.println(VSpeed);
        
        if (VSpeed != 0) {
            stepperMotor.setSpeed(SSPEED * (b_direction ? -1 : 1) * VSpeed);
            stepperMotor.runSpeed();
        }
    }
    
    /// Обновление
    void Update() {
        if (b_canMove) {
            pedal.Update();
            Move();
        }
    }
};

#endif
