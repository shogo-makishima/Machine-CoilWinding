#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_

#include "Rect.h"

#define MAX_LENGTH_NAME 16
#define MAX_TEXT_LENGHT 32

/// Объект мира
struct UIObject {
    /// Название объекта
    char Name[MAX_LENGTH_NAME];
    /// Прямоугольник
    Rect rect;

    /// Функция перерисовки
    virtual void Repaint();
    /// Функция перемещения
    virtual void Move(int x, int y);
    /// Функция обновления
    virtual void Update();
};
 
#endif