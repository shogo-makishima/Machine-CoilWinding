#ifndef _CUSTOM_SERIAL_H_
#define _CUSTOM_SERIAL_H_

#include <AltSoftSerial.h>

/// Размер буффера на чтение
#define BUFFER_READ_SIZE 32
/// Кол-во комманд и аргументов в буффере
#define BUFFER_COMMAND_SIZE_1 8
/// Кол-во символов в команде или аргументе
#define BUFFER_COMMAND_SIZE_2 16

/// Надстройка для общения через порт
namespace CustomSerial {
    /// Кастомный порт
    AltSoftSerial customSerial;

    /// Буффер чтения
    char BUFFER_READ[BUFFER_READ_SIZE];
    /// Буффер отпарсенных команд
    char BUFFER_COMMAND[BUFFER_COMMAND_SIZE_1][BUFFER_COMMAND_SIZE_2];

    /// Поиск совпадений для регулярных выражений
    MatchState matchState;

    /// Каретка чтения
    byte caretReadPosition = 0;
    /// Каретка команд
    byte caretCommandPosition = 0;

    /// Можно ли парсить буффер, true - пришел символ конца строки
    bool b_bufferIsFull = false;

    /// Очистить буффер
    void ClearBuffer() {
        for (byte i = 0; i < BUFFER_READ_SIZE; i++)
            BUFFER_READ[i] = '\0';
    }

    /// Вывести в debug port содержимое буффера
    void PrintBuffer() {
        Serial.print("[DEBUG] ");
        for (byte i = 0; i < BUFFER_READ_SIZE; i++)
            Serial.print(BUFFER_READ[i]);
        Serial.println();
    }

    /// Отправить данные
    void SendSettingsData() {
        customSerial.print("D20 ");
        customSerial.println((long)Data::dataContainer.countTurn);

        customSerial.print("D21 ");
        customSerial.println((Data::dataContainer.b_canMove) ? 1 : 0);

        customSerial.print("D22 ");
        customSerial.println((Data::dataContainer.b_mode) ? 1 : 0);

        customSerial.print("D23 ");
        customSerial.println((Data::dataContainer.b_direction) ? 1 : 0);

        customSerial.print("D24 ");
        customSerial.println(Data::dataContainer.limit_countTurn);
    }

    /// Отпарсить буффер
    void ParseBuffer() {
        matchState.Target(BUFFER_READ);

        unsigned int index = 0;
        caretCommandPosition = 0;

        char PARSE_BUFFER [64];
        while (true) {
            char result = matchState.Match ("([0-9A-Z]+)", index);

            if (result == REGEXP_MATCHED) {
                strcpy(BUFFER_COMMAND[caretCommandPosition], matchState.GetCapture (PARSE_BUFFER, 0));
                caretCommandPosition++;
                index = matchState.MatchStart + matchState.MatchLength;
            } else break;
        }

        if (strcmp(BUFFER_COMMAND[0], "M0") == 0) {
            Data::dataContainer.b_canMove = true;
        } else if (strcmp(BUFFER_COMMAND[0], "M1") == 0) {
            Data::dataContainer.b_canMove = false;
        } else if (strcmp(BUFFER_COMMAND[0], "M3") == 0) {
            Data::dataContainer.b_direction = true;
        } else if (strcmp(BUFFER_COMMAND[0], "M4") == 0) {
            Data::dataContainer.b_direction = false;
        } else if (strcmp(BUFFER_COMMAND[0], "M7") == 0) {
            Data::dataContainer.b_mode = true;
        } else if (strcmp(BUFFER_COMMAND[0], "M8") == 0) {
            Data::dataContainer.b_mode = false;
        } else if (strcmp(BUFFER_COMMAND[0], "M10") == 0) {
            Data::dataContainer.countTurn = 0;
            CoilWinding::last_countTurn = 0;
            CoilWinding::stepperMotor.setCurrentPosition(0);
        } else if (strcmp(BUFFER_COMMAND[0], "M12") == 0) {
            Data::Save();
        } else if (strcmp(BUFFER_COMMAND[0], "M13") == 0) {
            Data::Load();
            CoilWinding::stepperMotor.setCurrentPosition(Data::dataContainer.currentPosition);
            
            SendSettingsData();
        } else if (strcmp(BUFFER_COMMAND[0], "M14") == 0) {
            Data::Clear();
            CoilWinding::stepperMotor.setCurrentPosition(Data::dataContainer.currentPosition);

            SendSettingsData();
        } else if (strcmp(BUFFER_COMMAND[0], "M20") == 0) {
            customSerial.print("D20 ");
            customSerial.println(Data::dataContainer.countTurn);
        } else if (strcmp(BUFFER_COMMAND[0], "M21") == 0) {
            customSerial.print("D21 ");
            customSerial.println((Data::dataContainer.b_canMove) ? 1 : 0);
        } else if (strcmp(BUFFER_COMMAND[0], "M22") == 0) {
            customSerial.print("D22 ");
            customSerial.println((Data::dataContainer.b_mode) ? 1 : 0);
        } else if (strcmp(BUFFER_COMMAND[0], "M23") == 0) {
            customSerial.print("D23 ");
            customSerial.println((Data::dataContainer.b_direction) ? 1 : 0);
        } else if (strcmp(BUFFER_COMMAND[0], "M24") == 0) {
            customSerial.print("D24 ");
            customSerial.println(Data::dataContainer.limit_countTurn);
        } else if (strcmp(BUFFER_COMMAND[0], "M25") == 0) {
            customSerial.print("D25 ");
            customSerial.println(Data::dataContainer.b_mainDirection);
        } else if (strcmp(BUFFER_COMMAND[0], "M26") == 0) {
            customSerial.print("D26 ");
            customSerial.println(Data::dataContainer.speed);
        } else if (strcmp(BUFFER_COMMAND[0], "M30") == 0) {
            Data::dataContainer.limit_countTurn = atoi(BUFFER_COMMAND[1]) / 10.0f;
        } else if (strcmp(BUFFER_COMMAND[0], "M31") == 0) {
            Data::dataContainer.b_mainDirection = !(strcmp(BUFFER_COMMAND[1], "0") == 0);
        } else if (strcmp(BUFFER_COMMAND[0], "M32") == 0) {
            Data::dataContainer.speed = atoi(BUFFER_COMMAND[1]);
            CoilWinding::SetSpeed(Data::dataContainer.speed);
        }
    }

    /// Считать байт из буфера
    void ReadByte() {
        if (customSerial.available()) {
            byte symbolASCII = customSerial.read();
            
            if (symbolASCII == 10) {
                b_bufferIsFull = true;
                caretReadPosition = 0;
            } else {
                BUFFER_READ[caretReadPosition] = char(symbolASCII);
                caretReadPosition++;
            }
        }
    }
};

#endif