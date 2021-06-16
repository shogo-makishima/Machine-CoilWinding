#ifndef _CUSTOM_SERIAL_H_
#define _CUSTOM_SERIAL_H_

/// Размер буффера на чтение
#define BUFFER_READ_SIZE 32
/// Кол-во комманд и аргументов в буффере
#define BUFFER_COMMAND_SIZE_1 8
/// Кол-во символов в команде или аргументе
#define BUFFER_COMMAND_SIZE_2 16

#include "UTFT_Menu/Pages/Variables.h"

/// Надстройка для общения через порт
namespace CustomSerial {
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
        for (byte i = 0; i < BUFFER_READ_SIZE; i++)
            Serial.print(BUFFER_READ[i]);
        Serial.println();
    }

    /// Отпарсить буффер
    void ParseBuffer() {
        matchState.Target(BUFFER_READ);

        unsigned int index = 0;
        caretCommandPosition = 0;

        char PARSE_BUFFER [64];
        while (true) {
            char result = matchState.Match ("(-?[0-9A-Z]+[.]?[0-9A-Z]*)", index);

            if (result == REGEXP_MATCHED) {
                strcpy(BUFFER_COMMAND[caretCommandPosition], matchState.GetCapture (PARSE_BUFFER, 0));
                caretCommandPosition++;
                index = matchState.MatchStart + matchState.MatchLength;
            } else break;
        }

        if (strcmp(BUFFER_COMMAND[0], "D20") == 0) {
            localCountTurn = atol(BUFFER_COMMAND[1]);
            if (wasLoad_CountAxis < 2) wasLoad_CountAxis++;
        }  else if (strcmp(BUFFER_COMMAND[0], "D21") == 0) {
            localCanMove = !(strcmp(BUFFER_COMMAND[1], "0") == 0);
            if (wasLoad_CanMove < 2) wasLoad_CanMove++;
        } else if (strcmp(BUFFER_COMMAND[0], "D22") == 0) {
            localMode = !(strcmp(BUFFER_COMMAND[1], "0") == 0);
            if (wasLoad_Mode < 2) wasLoad_Mode++;
        } else if (strcmp(BUFFER_COMMAND[0], "D23") == 0) {
            localDirection = !(strcmp(BUFFER_COMMAND[1], "0") == 0);
            if (wasLoad_Direction < 2) wasLoad_Direction++;
        }  else if (strcmp(BUFFER_COMMAND[0], "D24") == 0) {
            VariableController::LimitFromFloat(atof(BUFFER_COMMAND[1]));
            if (wasLoad_Limit < 2) wasLoad_Limit++;
        } 
    }

    /// Считать байт из буфера
    void ReadByte() {
        if (Serial1.available()) {
            byte symbolASCII = Serial1.read();

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