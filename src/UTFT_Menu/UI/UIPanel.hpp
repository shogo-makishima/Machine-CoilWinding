#ifndef _UIPANEL_H_
#define _UIPANEL_H_

#include "UTFT_Menu/Menus.h"

class UIPanel : public UIObject {
    private:
    public:
    char* Name;
    Rect rect;
    uint16_t Color;

    UIPanel(char* getName, Rect getRect, uint16_t getColor) : Name(getName), rect(getRect), Color(getColor) {}

    void Repaint() override {
        GLCD.setColor(Color);
        GLCD.fillRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
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