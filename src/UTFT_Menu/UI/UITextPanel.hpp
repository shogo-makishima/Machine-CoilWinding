#ifndef _UITEXTPANEL_H_
#define _UITEXTPANEL_H_

#include "UTFT_Menu/Menus.h"

/// Простая панель с текстом
class UITextPanel : public UIObject {
    private:
    public:
    char Name[MAX_LENGTH_NAME];
    Rect rect;

    /// Сслылка на текст
    Text& text;
    /// Прямоугольник для текста
    Vector2D textRect;
    /// Основной цвет
    uint16_t Color;
    /// Цвет текста
    uint16_t ColorText;
    /// Шрифт
    const GFXfont *Font;

    /// Базовый конструктор
    UITextPanel(char getName[MAX_LENGTH_NAME], Rect getRect, Vector2D getTextRect, Text& getText, uint16_t getColorText, uint16_t getColor, const GFXfont *font = &DEFAULT_FONT) : rect(getRect), textRect(getTextRect), text(getText), ColorText(getColorText), Color(getColor), Font(font) {
        strcpy(Name, getName);
    }

    void Repaint() override {
        GLCD.fillRect(rect.x, rect.y, rect.w, rect.h, Color);
        
        GLCD.setFont(Font);
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