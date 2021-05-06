#ifndef _COILWINDING_H_
#define _COILWINDING_H_

#include "Libraries/AccelStepper/src/AccelStepper.h"
#include "Libraries/AccelStepper/src/MultiStepper.h"
// #include "Libraries/CustomStepper/CustomStepper.hpp"
#include "UTFT_Menu/Utilites/Timer.h"

#define ENA 25 // Пин первой обмотки
#define ENB 35 // Пин второй обмотки

#define STEPS 200 // Количество шагов на один оборот
#define MSPEED 200 // Масимальная скорость
#define SSPEED 100 // Базовая скорость

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
    double countSteps = 0.0f;
    /// Кол-во оборотов
    long int countAxis = 0;
    /// Время действия "скорости"
    double rotationTime = 0.0f;
    /// Дополнительное хранение времени
	double m_timing;
    /// Последняя скорость
    float lastVSpeed = 0.0f;
    /// Кол-во скоростей
    short int countSpeed = 0;
    /// Сумма скоростей
    double sumSpeed = 0.0f;

    /// Направление
    bool b_direction = true;

    /// Шаговый двигатель
    AccelStepper stepperMotor(AccelStepper::FULL4WIRE, 27, 29, 31, 33);
    /// Для вращения двигателей
    long positions[1] = { STEPS };

    /// Создание
    void Init() {
        pinMode(PEDAL_PIN, INPUT);

        pinMode(ENA, OUTPUT);
        pinMode(ENB, OUTPUT);

        stepperMotor.setMaxSpeed(MSPEED); // Устанавливаем скорость вращения об./мин.
        stepperMotor.setSpeed(-SSPEED); // Устанавливаем скорость вращения об./мин.
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
        // Serial.println(VSpeed);

        if (VSpeed != 0) {
            SetBlock(true);
            /*
            m_timing = millis() / pow(10, 6);

            countSteps += (lastVSpeed * SSPEED) * (m_timing - rotationTime) * (b_direction ? 1 : -1);
            */
            /*
            if (rotationTime >= 0.5f) {
                float mediumSpeed = sumSpeed / countSpeed;
                countSteps += mediumSpeed * rotationTime * (b_direction ? 1 : -1);

                countAxis = countSteps / STEPS;

                m_timing = millis() / pow(10, 6);
                rotationTime = 0;

                sumSpeed = 0;
                countSpeed = 0;
            }
            
            sumSpeed += (VSpeed * SSPEED * (b_direction ? 1 : -1));
            countSpeed++;

            rotationTime += (millis() - m_timing) / pow(10, 6);
            */
            
            if (VSpeed != lastVSpeed) {
                countSteps += (SSPEED * lastVSpeed) * rotationTime * (b_direction ? 1 : -1);

                m_timing = millis() / pow(10, 4);
                rotationTime = 0;
            } else if (rotationTime >= 0.5f) {
                countSteps += (SSPEED * VSpeed) * rotationTime * (b_direction ? 1 : -1);

                m_timing = millis() / pow(10, 4);
                rotationTime = 0;
            }

            rotationTime += ((millis()) / pow(10, 4) - m_timing);
            
            stepperMotor.setSpeed(SSPEED * (b_direction ? -1 : 1) * VSpeed);
            stepperMotor.runSpeed();
        } else {
            SetBlock(false);
            rotationTime = 0;
        }

        Serial.println(countSteps);
        lastVSpeed = VSpeed;
    }
    
    /// Обновление
    void Update() {
        if (b_canMove) {
            pedal.Update();
            Move();
        } else {
            SetBlock(false);
        }
    }
};

#endif
