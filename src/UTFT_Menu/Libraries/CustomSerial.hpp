#ifndef _CUSTOM_SERIAL_H_
#define _CUSTOM_SERIAL_H_

#define BUFFER_READ_SIZE 32
#define BUFFER_COMMAND_SIZE_1 8
#define BUFFER_COMMAND_SIZE_2 16

#include "UTFT_Menu/Pages/Variables.h"

namespace CustomSerial {
    char BUFFER_READ[BUFFER_READ_SIZE];
    char BUFFER_COMMAND[BUFFER_COMMAND_SIZE_1][BUFFER_COMMAND_SIZE_2];

    MatchState matchState;

    byte caretReadPosition = 0;
    byte caretWritePosition = 0;
    byte caretCommandPosition = 0;

    bool b_bufferIsFull = false;

    void ClearBuffer() {
        for (byte i = 0; i < BUFFER_READ_SIZE; i++)
            BUFFER_READ[i] = '\0';
    }

    void PrintBuffer() {
        for (byte i = 0; i < BUFFER_READ_SIZE; i++)
            Serial.print(BUFFER_READ[i]);
        Serial.println();
    }

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
            localCountAxis = atol(BUFFER_COMMAND[1]);
            wasLoad_CountAxis++;
        } else if (strcmp(BUFFER_COMMAND[0], "D21") == 0) {
            if (strcmp(BUFFER_COMMAND[1], "0") == 0) localCanMove = false;
            else localCanMove = true;
            wasLoad_CanMove++;
        } else if (strcmp(BUFFER_COMMAND[0], "D22") == 0) {
            if (strcmp(BUFFER_COMMAND[1], "0") == 0) localMode = false;
            else localMode = true;
            wasLoad_Mode++;
        }else if (strcmp(BUFFER_COMMAND[0], "D23") == 0) {
            if (strcmp(BUFFER_COMMAND[1], "0") == 0) localDirection = false;
            else localDirection = true;
            wasLoad_Direction++;
        } 
    }

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