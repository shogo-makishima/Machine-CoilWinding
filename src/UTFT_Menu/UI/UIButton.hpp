#ifndef _UIBUTTON_H_
#define _UIBUTTON_H_

#include "UTFT_Menu/Menus.h"

typedef void(*callbackButtonPress)();

class UIButton : public UIObject {
    private:
    public:
    char* Name;
    char* text;
    Rect rect;
    Vector2D textRect;
    uint16_t Color;
    uint16_t PressColor;
    uint16_t ColorText;
    callbackButtonPress Press;
    bool b_lastTouch = false;

    UIButton(char* getName, Rect getRect, Vector2D getTextRect, char* getText, uint16_t getColorText, uint16_t getColor, uint16_t getPressColor, callbackButtonPress callback = []{Serial.println("PRESS!");}) : Name(getName), rect(getRect), textRect(getTextRect), text(getText), ColorText(getColorText), Color(getColor), PressColor(getPressColor), Press(callback) {}

    void Repaint() override {
        GLCD.setColor(Color);
        GLCD.fillRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
        
        GLCD.setColor(ColorText);
        GLCD.setBackColor(VGA_TRANSPARENT);
        GLCD.setFont(DEFAULT_FONT);
        
        GLCD.print(text, rect.x + textRect.x, rect.y + textRect.y);
    }

    void Move(int x, int y) override {
        GLCD.setColor(BACKGDOUND);
        GLCD.fillRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);

        rect.x = x; rect.y = y;
        Repaint();
    }

    bool OnClick() {
        return b_isTouch && (rect.x <= TOUCH.getX() && rect.x + rect.w > TOUCH.getX() && rect.y <= TOUCH.getY() && rect.y + rect.h > TOUCH.getY());
    }

    void Update() override {
        bool b_currentTouch = OnClick();
        if (b_currentTouch && !b_lastTouch) { 
            Press();
            // uint16_t t_color = Color;
            // Color = PressColor;
            // Repaint();
            // Color = t_color;
            // Repaint();
        }

        b_lastTouch = b_currentTouch;
    }
};


#endif