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
        new UIButton("ENTER", { 0, 0, 216, 48 }, { 12, 12 }, SPEED, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            if (VMode) PAGES::ChangePageFormName("SpeedControlPage");
        }),
        new UICheckBox("ENTER", { 264, 0, 216, 48 }, { 12, 12 }, MODE, BLACK, RED, GREEN, VMode),

        new UITextPanel("VCounter", { 0, 72, 288, 168 }, { 12, 12 }, counterText, BLACK, WHITE_L_80),
        new UICheckBox("ENTER", { 312, 72, 168, 168 }, { 12, 12 }, DIRECTION, BLACK, RED, GREEN, CoilWinding::b_direction),
        
        new UIButton("ENTER", { 0, 264, 480, 48 }, { 12, 12 }, CLEAR, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            CoilWinding::countAxis = 0;
            CoilWinding::countSteps = 0;
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
        counterText.SetText(0);
        RepaintAll();
    }

    void Update() override {
        if (CoilWinding::countAxis != lastCounter) {
            counterText.SetText((int)CoilWinding::countAxis);
            UIObjects[2]->Repaint();
            lastCounter = CoilWinding::countAxis;
        }

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }

        CoilWinding::VCanMove = true;
    }
};

#endif