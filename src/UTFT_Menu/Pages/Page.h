#ifndef _MENU_ABSTRACT_H_
#define _MENU_ABSTRACT_H_

#include "UTFT_Menu/Menus.h"

class Page {
    public:
    char* Name;

    char* LastMenuName;

    UIObject* UIObjects[MAX_OBJECTS_ON_PAGE];

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    
    void RepaintByIndex(int index) {
        if (UIObjects[index] == NULL) return;
        UIObjects[index]->Repaint();
    }

    void RepaintAll() {
        GLCD.fillScr(BACKGDOUND);

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Repaint();
        }
    }
};

class Empty : public Page {
    private:

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        NULL,
    };

    Empty(char* getName) {
        Name = getName;
        
        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            UIObjects[i] = localObjects[i];
        }
    }

    void Awake() override {
        
    }

    void Start() override {
        RepaintAll();
    }

    void Update() override {
        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }
    }
};

#endif