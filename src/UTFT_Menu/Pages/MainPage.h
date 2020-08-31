#ifndef _MAINPAGE_H_
#define _MAINPAGE_H_

#include "PagesManager.h"
#include "UTFT_Menu/Menus.h"

class MainPage : public Page {
    private:
    Text uiSymbol_1 = { "0" };

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UIButton("ENTER", { 0, 264, 480, 48 }, { 12, 12 }, SPEED, BLACK, WHITE_L_80, WHITE_L_5, [] { 
            PAGES::ChangePageFormName("SpeedControlPage");
        }),
        NULL,
    };

    MainPage(char* getName) {
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