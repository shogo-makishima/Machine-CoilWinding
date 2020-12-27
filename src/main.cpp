#include <Arduino.h>
#include <Scheduler/src/Scheduler.h>
#include <pt/pt.h>
#include "UTFT_Menu/Menus.h"


static struct pt pt1;
static int loopMotor(struct pt *pt) {
    static unsigned long lastTimeBlink = 0;
    PT_BEGIN(pt);
        while (true) {
            CoilWinding::Update();
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
            lastTimeBlink = millis();
            PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 10);
    }
    PT_END(pt);
}


void setup() {
    INIT();
    
    PT_INIT(&pt1);
    PT_INIT(&pt2);
}

void loop() {
    loopDisplay(&pt2);
    loopMotor(&pt1);
}