#ifndef _TOUCHEMULATOR_H_
#define _TOUCHEMULATOR_H_

#include "Stream.h"
#include "UTFT_Menu/Menus.h"

#define TOUCH_COUNT 8

static bool b_isTouch = false;
static int i_touchTimer = 0;
static bool b_lastState = false;

class TouchEmulator {
    public:
    int x = 0, y = 0;

    Timer touchTimer = Timer(50, [] {
        b_isTouch = false;
    });

    void InitTouch() {}
    void setPrecision(int value) {}

    void CheckTouch(TSPoint point) {
        x = GLCD.LCD_HEIGHT - point.x;
        y = GLCD.LCD_WIDTH - point.y;

        b_isTouch = !(!Math::InRange(0, GLCD.LCD_HEIGHT, x) && !Math::InRange(0, GLCD.LCD_WIDTH, y));

        if (b_lastState != b_isTouch) {
            i_touchTimer++;
            if (i_touchTimer >= TOUCH_COUNT) {
                b_lastState = b_isTouch;
                b_isTouch = !b_isTouch;
                i_touchTimer = 0;
            }
        }
    }

    int getX() { return x; }
    int getY() { return y; }
    void Update() {
        TSPoint point = GLCD.getPoint();
        GLCD.normalizeTsPoint(point);

        CheckTouch(point);
        // touchTimer.Update();
    }
};

#endif
