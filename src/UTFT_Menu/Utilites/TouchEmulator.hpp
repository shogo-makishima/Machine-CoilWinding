#ifndef _TOUCHEMULATOR_H_
#define _TOUCHEMULATOR_H_

#include "Stream.h"
#include "UTFT_Menu/Menus.h"

#define TOUCH_COUNT 4
#define TOUCH_RANGE 10
#define TOUCH_COUNT_Z 4

static bool b_isTouch = false;
static int i_touchTimer = 0;
static int i_touchZ= 0;

class TouchEmulator {
    public:
    int x = 0, y = 0, z = 0;

    void InitTouch() {}
    void setPrecision(int value) {}

    void CheckTouch(TSPoint point) {
        if (point.z == 0 && i_touchZ < TOUCH_RANGE) {
            i_touchZ++;
            return;
        }

        if (point.z == 0 && i_touchZ >= TOUCH_RANGE) {
            i_touchZ = 0;
        }


        x = GLCD.LCD_HEIGHT - point.x;
        y = GLCD.LCD_WIDTH - point.y;
        z = point.z;

        bool t_isTouch = !(!Math::InRange(0, GLCD.LCD_HEIGHT, x) && !Math::InRange(0, GLCD.LCD_WIDTH, y) && z != 0);

        if (!t_isTouch) {
            i_touchTimer++;
            if (i_touchTimer >= TOUCH_COUNT) {
                b_isTouch = t_isTouch;
            }
        } else {
            b_isTouch = t_isTouch;
            i_touchTimer = 0;
        }

        // Serial.println("B: " + String(b_isTouch) + " T: " + String(t_isTouch));
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
