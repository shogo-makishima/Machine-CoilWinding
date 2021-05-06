#ifndef _UICHECKBOX_H_
#define _UICHECKBOX_H_

#include "UTFT_Menu/Menus.h"

/// Класс поля выбора, два состояния: true, false
class UICheckBox : public UIObject {
    private:
    public:
    char* Name;
    Rect rect;

    /// Текст на CheckBox'е
    char* text;
    /// Прямоугольник для текста
    Vector2D textRect;
    /// Основной цвет
    uint16_t Color;
    /// Цвет после нажатия
    uint16_t PressColor;
    /// Цвет текста
    uint16_t ColorText;
    /// Шрифт
    const GFXfont *Font;
    /// Последнее нажатие
    bool b_lastTouch = false;
    /// Ссылка на переменную
    bool &variable_ref;

    /// Базовый конструктор
    UICheckBox(char* getName, Rect getRect, Vector2D getTextRect, char* getText, uint16_t getColorText, uint16_t getColor, uint16_t getPressColor, bool &variable, const GFXfont *font = &DEFAULT_FONT) : Name(getName), rect(getRect), textRect(getTextRect), text(getText), ColorText(getColorText), Color(getColor), PressColor(getPressColor), variable_ref(variable), Font(font) {}

    void Repaint() override {
        if (variable_ref) GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, PressColor);
        else GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, Color);
        
        GLCD.setFont(Font);
        GLCD.setTextColor(ColorText);
        GLCD.setCursor(rect.x + textRect.x, rect.y + textRect.y);
        GLCD.print(text);
    }

    void Move(int x, int y) override {
        GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, BACKGDOUND);

        rect.x = x; rect.y = y;
        Repaint();
    }

    /// Функция нажатия
    bool OnClick() {
        return b_isTouch && (rect.x <= TOUCH.getX() && rect.x + rect.w >= TOUCH.getX() && rect.y <= TOUCH.getY() && rect.y + rect.h >= TOUCH.getY());
    }

    void Update() override {
        bool b_currentTouch = OnClick();
        if (!b_currentTouch && b_lastTouch) {
            variable_ref = !variable_ref;
            Serial.println("REPAINT CHECK BOX! " + String(TOUCH.getX()));
            Repaint();
        }
        b_lastTouch = b_currentTouch;
    }
};


#endif