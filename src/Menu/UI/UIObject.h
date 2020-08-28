#ifndef _UIOBJECT_H_
#define _UIOBJECT_H_

#include "Rect.h"

struct UIObject {
    char* Name;
    Rect rect;

    virtual void Repaint();
    virtual void Move(int x, int y);
    virtual void Update();
};
 
#endif