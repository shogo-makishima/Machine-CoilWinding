#ifndef _UIPROGRESSBAR_H_
#define _UIPROGRESSBAR_H_

#include "UTFT_Menu/Menus.h"

/// Прогресс бар
class UIProgressBar : public UIObject {
    private:
    public:
    char Name[MAX_LENGTH_NAME];
    Rect rect;
    /// Последнее значение
    float lastValue = 0;
    /// Привязанная переменная
    float& value;
    /// Минимальное значение
    float _min;
    /// Максимальное значение
    float& _max;
    /// Отступ
    int offset;
    /// Цвет рамки
    uint16_t borderColor;
    /// Цвет фона полосы
    uint16_t backgroundLineColor;
    /// Цвет полосы
    uint16_t lineColor;

    /// Базовый конструктор
    UIProgressBar(char getName[MAX_LENGTH_NAME], Rect getRect, float getMin, float& getMax, int getOffset, float& getValue, uint16_t getBorderColor, uint16_t getBackgroundLineColor, uint16_t getLineColor) : rect(getRect), _min(getMin), _max(getMax), offset(getOffset), value(getValue), borderColor(getBorderColor), backgroundLineColor(getBackgroundLineColor), lineColor(getLineColor) {
        strcpy(Name, getName);
    }

    void Repaint() override {
        GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, BACKGDOUND);

        float widthBar = Math::Map(value, _min, _max, 0.0f, 1.0f) * rect.w - offset * 2;

        GLCD.drawRect(rect.x, rect.y, rect.w, rect.h, borderColor);
        Serial.println(widthBar);
        Serial.println(rect.x);
        GLCD.fillRect(rect.x + offset, rect.y + offset, widthBar, rect.h - offset * 2, lineColor);
    }

    void Move(int x, int y) override {
        GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, BACKGDOUND);

        rect.x = x; rect.y = y;
        Repaint();
    }

    void Update() override {
        if (value != lastValue) {
            Repaint();
        }

        lastValue = value;
    }
};


#endif