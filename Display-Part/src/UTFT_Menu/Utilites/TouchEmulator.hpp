#ifndef _TOUCHEMULATOR_H_
#define _TOUCHEMULATOR_H_

#include "Timer.h"
#include "Stream.h"
#include "UTFT_Menu/Menus.h"

#define TOUCH_COUNT 4
#define TOUCH_RANGE 10
#define TOUCH_COUNT_Z 4
#define DEATH_TIMER 250

/// Было ли касание
static bool b_isTouch = false;
/// Кол-во касаний до срабатывания
static int i_touchTimer = 0;
/// Кол-во касаний до срабатывания по Z
static int i_touchZ= 0;

class TouchEmulator {
    public:
    /// Координаты
    int x = 0, y = 0, z = 0;
    /// Можно ли читать значения с тачскрина
    bool b_canReadTouch = true;
    /// Мертвый таймер, обнуляющийся при переходе на дургую страницу
    Timer deathTimer = Timer(DEATH_TIMER, [&] { b_canReadTouch = true; });

    /// Запустить тач
    void InitTouch() {}
    /// Пустая функция ;)
    void setPrecision(int value) {}

    /// Проверить касание
    void CheckTouch(TSPoint point) {
        if (!b_canReadTouch) return;

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
    }

    /// Получить X
    int getX() { return x; }
    /// Получить Y
    int getY() { return y; }
    /// Функция обновления
    void Update() {
        TSPoint point = GLCD.getPoint();
        GLCD.normalizeTsPoint(point);
        deathTimer.Update();
        CheckTouch(point);
        // touchTimer.Update();
    }
};

#endif
