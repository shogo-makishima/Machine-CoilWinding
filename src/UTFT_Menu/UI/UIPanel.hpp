#ifndef _UIPANEL_H_
#define _UIPANEL_H_

#include "UTFT_Menu/Menus.h"

/// Простая панель
class UIPanel : public UIObject {
    private:
    public:
    char Name[MAX_LENGTH_NAME];
    Rect rect;
    
    /// Основной цвет
    uint16_t Color;

    /// Базовый конструктор
    UIPanel(char getName[MAX_LENGTH_NAME], Rect getRect, uint16_t getColor) : rect(getRect), Color(getColor) {
        strcpy(Name, getName);
    }

    void Repaint() override {
        GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, Color);
    }

    void Move(int x, int y) override {
        GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, BACKGDOUND);

        rect.x = x; rect.y = y;
        Repaint();
    }

    void Update() override {}
};


#endif