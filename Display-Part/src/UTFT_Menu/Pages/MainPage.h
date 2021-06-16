#ifndef _MAINPAGE_H_
#define _MAINPAGE_H_

#include "PagesManager.h"
#include "UTFT_Menu/Menus.h"

#define CHANGE_PAGE_AXIS_BUTTON_ID 0

class MainPage : public Page {
    private:
    Text counterText = { "0" };
    Text limitText = { "-" };
    // float lastCounter = 0;
    long lastCounter = 0;
    float last_Limit = 0.0f;
    bool last_Mode = false;

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
            localCountTurn = 0;
        }),
        //164

        new UITextPanel("VCounter", { 0, 82, 230, 50 }, { 12, 40 }, counterText, BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UITextPanel("Limit", { 270, 82, 230, 50 }, { 12, 40 }, limitText, BLACK, WHITE_L_80, &FREE_SANS_24PT),


        new UIButton("Settings", { 170, 246, 140, 50 }, { 12, 30 }, SETTINGS, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            PAGES::ChangePageFormName("SettingsPage");
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
        // counterText.SetText(0);

        UpdateLimitText();
        RepaintAll();
    }

    void Update() override {
        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (!localMode && i == CHANGE_PAGE_AXIS_BUTTON_ID) continue;
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }

        if (localCountTurn != lastCounter) {
            counterText.SetText(localCountTurn);
            UIObjects[5]->Repaint();
        }

        if (last_Mode != localMode || last_Limit != localLimit) {
            UpdateLimitText();
            UIObjects[6]->Repaint();
        }

        last_Limit = localLimit;
        lastCounter = localCountTurn;
        last_Mode = localMode;
    }

    void UpdateLimitText() {
        if (localMode) limitText.SetText(localLimit);
        else limitText.SetText("-");
    }
};

#endif