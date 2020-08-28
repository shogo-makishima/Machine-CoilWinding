#ifndef _TOUCHEMULATOR_H_
#define _TOUCHEMULATOR_H_

#include "Stream.h"
#include "Timer.h"

static bool b_isTouch = false;

class TouchEmulator {
    public:
    int x = 0, y = 0;

    Timer touchTimer = Timer(100, [] {
        b_isTouch = false;
    });

    void ParseTouch(String touch) {
        String t_x = "";
        String t_y = "";
        bool t_isX = true;

        for (char chr : touch) {
            if (t_isX) t_isX = !(t_isX && chr == ' ');

            if (t_isX) t_x += chr;
            else if (!t_isX) t_y += chr;
        }

        x = t_x.toInt();
        y = t_y.toInt();

        b_isTouch = true;
        touchTimer.Reset();
    }

    int getX() { return x; }
    int getY() { return y; }
    void Update() { touchTimer.Update(); }
};

#endif
