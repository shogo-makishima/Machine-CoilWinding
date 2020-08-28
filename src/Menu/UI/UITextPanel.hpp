#ifndef _UITEXTPANEL_H_
#define _UITEXTPANEL_H_

#include "Menu/Menus.h"

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
        GLCD.setColor(Color);
        GLCD.fillRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
        
        GLCD.setColor(ColorText);
        GLCD.setBackColor(VGA_TRANSPARENT);
        GLCD.setFont(DEFAULT_FONT);
        
        GLCD.print(text.text, rect.x + textRect.x, rect.y + textRect.y);
    }

    void Move(int x, int y) override {
        GLCD.setColor(BACKGDOUND);
        GLCD.fillRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);

        rect.x = x; rect.y = y;
        Repaint();
    }

    void Update() override {}
};


#endif