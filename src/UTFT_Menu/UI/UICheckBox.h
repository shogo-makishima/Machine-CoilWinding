#ifndef _UICHECKBOX_H_
#define _UICHECKBOX_H_

#include "UTFT_Menu/Menus.h"

class UICheckBox : public UIObject {
    private:
    public:
    char* Name;
    char* text;
    Rect rect;
    Vector2D textRect;
    uint16_t Color;
    uint16_t PressColor;
    uint16_t ColorText;
    bool b_lastTouch = false;
    bool &variable_ref;

    UICheckBox(char* getName, Rect getRect, Vector2D getTextRect, char* getText, uint16_t getColorText, uint16_t getColor, uint16_t getPressColor, bool &variable) : Name(getName), rect(getRect), textRect(getTextRect), text(getText), ColorText(getColorText), Color(getColor), PressColor(getPressColor), variable_ref(variable) {}

    void Repaint() override {
        if (variable_ref) GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, PressColor);
        else GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, Color);
        
        GLCD.setTextColor(ColorText);
        GLCD.setCursor(rect.x + textRect.x, rect.y + textRect.y);
        GLCD.print(text);
    }

    void Move(int x, int y) override {
        GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, BACKGDOUND);

        rect.x = x; rect.y = y;
        Repaint();
    }

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