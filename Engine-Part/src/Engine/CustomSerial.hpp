#ifndef _CUSTOM_SERIAL_H_
#define _CUSTOM_SERIAL_H_

#include <AltSoftSerial.h>

#define BUFFER_READ_SIZE 32
#define BUFFER_COMMAND_SIZE_1 8
#define BUFFER_COMMAND_SIZE_2 16

namespace CustomSerial {
    AltSoftSerial customSerial; // RX, TX

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
            char result = matchState.Match ("([0-9A-Z]+)", index);

            if (result == REGEXP_MATCHED) {
                strcpy(BUFFER_COMMAND[caretCommandPosition], matchState.GetCapture (PARSE_BUFFER, 0));
                caretCommandPosition++;
                index = matchState.MatchStart + matchState.MatchLength;
            } else break;
        }

        if (strcmp(BUFFER_COMMAND[0], "M0") == 0) {
            CoilWinding::b_canMove = true;
        } else if (strcmp(BUFFER_COMMAND[0], "M1") == 0) {
            CoilWinding::b_canMove = false;
        } else if (strcmp(BUFFER_COMMAND[0], "M3") == 0) {
            CoilWinding::b_direction = true;
        } else if (strcmp(BUFFER_COMMAND[0], "M4") == 0) {
            CoilWinding::b_direction = false;
        } else if (strcmp(BUFFER_COMMAND[0], "M7") == 0) {
            CoilWinding::b_mode = true;
        } else if (strcmp(BUFFER_COMMAND[0], "M8") == 0) {
            CoilWinding::b_mode = false;
        } else if (strcmp(BUFFER_COMMAND[0], "M10") == 0) {
            CoilWinding::countAxis = 0;
            CoilWinding::last_countAxis = 0;
            CoilWinding::stepperMotor.setCurrentPosition(0);
        } else if (strcmp(BUFFER_COMMAND[0], "M20") == 0) {
            customSerial.print("D20 ");
            customSerial.println(CoilWinding::countAxis);
        } else if (strcmp(BUFFER_COMMAND[0], "M21") == 0) {
            customSerial.print("D21 ");
            customSerial.println((CoilWinding::b_canMove) ? 1 : 0);
        } else if (strcmp(BUFFER_COMMAND[0], "M22") == 0) {
            customSerial.print("D22 ");
            customSerial.println((CoilWinding::b_mode) ? 1 : 0);
        } else if (strcmp(BUFFER_COMMAND[0], "M23") == 0) {
            customSerial.print("D23 ");
            customSerial.println((CoilWinding::b_direction) ? 1 : 0);
        }
    }

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