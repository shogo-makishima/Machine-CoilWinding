#ifndef _MAINPAGE_H_
#define _MAINPAGE_H_

#include "PagesManager.h"
#include "UTFT_Menu/Menus.h"

class MainPage : public Page {
    private:
    Text counterText = { "0" };
    int lastCounter = 0;

    Timer axisUpdate = Timer(1000, [] {ChangeVCounter();});

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UIButton("ENTER", { 0, 0, 216, 48 }, { 12, 12 }, SPEED, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            if (VMode) PAGES::ChangePageFormName("SpeedControlPage");
        }),
        new UICheckBox("ENTER", { 264, 0, 216, 48 }, { 12, 12 }, MODE, BLACK, RED, GREEN, VMode),

        new UITextPanel("VCounter", { 0, 72, 288, 168 }, { 12, 12 }, counterText, BLACK, WHITE_L_80),
        new UICheckBox("ENTER", { 312, 72, 168, 168 }, { 12, 12 }, DIRECTION, BLACK, RED, GREEN, VDirection),
        
        new UIButton("ENTER", { 0, 264, 480, 48 }, { 12, 12 }, CLEAR, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            VCounter = 0;
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
        counterText.SetText(VCounter);
        RepaintAll();
    }

    void Update() override {
        axisUpdate.Update();

        if (VCounter != lastCounter) {
            counterText.SetText(VCounter);
            UIObjects[2]->Repaint();
            lastCounter = VCounter;
        }

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }
    }
};

#endif