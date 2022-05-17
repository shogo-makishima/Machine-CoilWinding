#include <Arduino.h>

#include <pt/pt.h>
#include "UTFT_Menu/Menus.h"

void Read() {
    CustomSerial::ReadByte();
    if (CustomSerial::b_bufferIsFull) {
        CustomSerial::PrintBuffer();
        CustomSerial::ParseBuffer();
        CustomSerial::ClearBuffer();
        CustomSerial::b_bufferIsFull = false;
    }
}

static struct pt pt1;
static int loopMotor(struct pt *pt) {
    static unsigned long lastTimeBlink = 0;
    PT_BEGIN(pt);
        while (true) {
            VariableController::CheckVariable();
            Read();
            
            lastTimeBlink = millis();
            PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 10);
        }
    PT_END(pt);
}

static struct pt pt2;
static int loopDisplay(struct pt *pt) {
    static unsigned long lastTimeBlink = 0;
    PT_BEGIN(pt);
        while (true) {
            PAGES::UpdateCurrentPage();
            TOUCH.Update();
            // Serial.println(freeRAM());
            lastTimeBlink = millis();
            PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 10);
        }
    PT_END(pt);
}


void setup() {
    InitSerial();

    delay(5000);

    while (wasLoad_Mode < 2 || wasLoad_CanMove < 2 || wasLoad_Direction < 2 || wasLoad_Limit < 2 || wasLoad_MainDirection < 2 || wasLoad_Speed < 2) {
        VariableController::Awake();
        Read();
    }

    InitDisplay();  

    PT_INIT(&pt1);
    PT_INIT(&pt2);

    Serial1.println("M33");
}

void loop() {
    loopDisplay(&pt2);
    loopMotor(&pt1);
}