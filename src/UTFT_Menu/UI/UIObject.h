#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_

#include "Rect.h"

/// Объект мира
struct UIObject {
    /// Название объекта
    char* Name;
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