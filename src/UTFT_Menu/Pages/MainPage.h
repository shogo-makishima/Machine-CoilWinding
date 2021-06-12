#ifndef _MAINPAGE_H_
#define _MAINPAGE_H_

#include "PagesManager.h"
#include "UTFT_Menu/Menus.h"

#define CHANGE_PAGE_AXIS_BUTTON_ID 0

class MainPage : public Page {
    private:
    Text counterText = { "0" };
    // float lastCounter = 0;
    long lastCounter = 0;

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UIButton("SpeedPage", { 0, 0, 230, 50 }, { 12, 30 }, SPEED, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            if (localMode) PAGES::ChangePageFormName("SpeedControlPage");
        }),
        new UICheckBox("Mode", { 270, 0, 230, 50 }, { 12, 30 }, MODE, BLACK, RED, GREEN, localMode),
        
        new UICheckBox("Run || Stop", { 0, 164, 140, 50 }, { 12, 30 }, RUN_OR_STOP, BLACK, RED, GREEN, localCanMove),
        new UICheckBox("Direction", { 170, 164, 140, 50 }, { 12, 30 }, DIRECTION, BLACK, RED, GREEN, localDirection),
        new UIButton("Clear", { 340, 164, 140, 50 }, { 12, 30 }, CLEAR, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            Serial1.println("M10");
            // localCountAxis = 0.0f;
            localCountAxis = 0;
        }),
        //164

        new UITextPanel("VCounter", { 0, 82, 230, 50 }, { 12, 40 }, counterText, BLACK, WHITE_L_80, &FREE_SANS_24PT),
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
        // counterText.SetText(0);
        RepaintAll();
    }

    void Update() override {
        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (!localMode && i == CHANGE_PAGE_AXIS_BUTTON_ID) continue;
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }

        if (localCountAxis != lastCounter) {
            counterText.SetText(localCountAxis);
            UIObjects[5]->Repaint();
        }

        lastCounter = localCountAxis;
    }
};

#endif