#ifndef _UITEXTPANEL_H_
#define _UITEXTPANEL_H_

#include "UTFT_Menu/Menus.h"

class UITextPanel : public UIObject {
    private:
    public:
    char* Name;
    Text& text;
    Rect rect;
    Vector2D textRect;
    uint16_t Color;
    uint16_t ColorText;

    UITextPanel(char* getName, Rect getRect, Vector2D getTextRect, Text& getText, uint16_t getColorText, uint16_t getColor) : Name(getName), rect(getRect), textRect(getTextRect), text(getText), ColorText(getColorText), Color(getColor) {}

    void Repaint() override {
        GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, Color);
        
        GLCD.setTextColor(ColorText);
        GLCD.setCursor(rect.x + textRect.x, rect.y + textRect.y);
        GLCD.print(text.text);
    }

    void Move(int x, int y) override {
        GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, BACKGDOUND);

        rect.x = x; rect.y = y;
        Repaint();
    }

    void Update() override {}
};


#endif