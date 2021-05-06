#ifndef _MAINPAGE_H_
#define _MAINPAGE_H_

#include "CoilWinding/CoilWinding.hpp"
#include "PagesManager.h"
#include "UTFT_Menu/Menus.h"



class MainPage : public Page {
    private:
    Text counterText = { "0" };
    long int lastCounter = 0;

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UIButton("SpeedPage", { 0, 0, 230, 50 }, { 12, 12 }, SPEED, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            if (VMode) PAGES::ChangePageFormName("SpeedControlPage");
        }),
        new UICheckBox("Mode", { 270, 0, 230, 50 }, { 12, 12 }, MODE, BLACK, RED, GREEN, VMode),
        
        new UICheckBox("Run || Stop", { 0, 164, 140, 50 }, { 12, 12 }, RUN_OR_STOP, BLACK, RED, GREEN, CoilWinding::b_canMove),
        new UICheckBox("Direction", { 170, 164, 140, 50 }, { 12, 12 }, DIRECTION, BLACK, RED, GREEN, CoilWinding::b_direction),
        new UIButton("Clear", { 340, 164, 140, 50 }, { 12, 12 }, CLEAR, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            CoilWinding::countAxis = 0;
            CoilWinding::countSteps = 0.0f;
        }),
        //164

        new UITextPanel("VCounter", { 0, 82, 230, 50 }, { 12, 12 }, counterText, BLACK, WHITE_L_80, &FREE_SANS_24PT),
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
        counterText.SetText(0);
        RepaintAll();
    }

    void Update() override {
        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }

        if (CoilWinding::countAxis != lastCounter) {
            counterText.SetText((int)CoilWinding::countAxis);
            UIObjects[3]->Repaint();
        }

        lastCounter = CoilWinding::countAxis;
    }
};

#endif