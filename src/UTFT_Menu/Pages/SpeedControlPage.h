#ifndef _SIMPLEPAGE_H_
#define _SIMPLEPAGE_H_

#include "PagesManager.h"
#include "UTFT_Menu/Menus.h"

void SetSpeedButtonsPress(int index, bool direction) {
    VSpeed[index] = VSpeed[index] + (1 * (direction) ? 1 : -1);
    VSpeed[index] = Math::Clamp(0, 9, VSpeed[index]);
}

Text uiSymbols[6] = { 
    { "0" },
    { "0" },
    { "0" },
    { "0" },
    { "0" },
    { "0" },
};

class SpeedControlPage : public Page {
    private:
    int lastUiInt[6] = {  0, 0, 0, 0, 0, };
    Text separteSymbol = { "." };

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UIButton("CLEAR", { 0, 8, 480, 48 }, { 12, 12 }, CLEAR, BLACK, WHITE_L_80, WHITE_L_5, [] { 
            ClearVSpeed();
        }),

        // TEXT SYMBOL 1
        new UIButton("X+", { 0, 72, 48, 48 }, { 12, 12 }, "+", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(0, true);
        }),
        new UITextPanel("X+", { 0, 136, 48, 48 }, { 12, 12 }, uiSymbols[0], BLACK, WHITE_L_80),
        new UIButton("X+", { 0, 200, 48, 48 }, { 12, 12 }, "-", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(0, false);
        }),

        // TEXT SYMBOL 2
        new UIButton("X+", { 72, 72, 48, 48 }, { 12, 12 }, "+", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(1, true);
        }),
        new UITextPanel("X+", { 72, 136, 48, 48 }, { 12, 12 }, uiSymbols[1], BLACK, WHITE_L_80),
        new UIButton("X+", { 72, 200, 48, 48 }, { 12, 12 }, "-", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(1, false);
        }),

        // TEXT SYMBOL 3
        new UIButton("X+", { 144, 72, 48, 48 }, { 12, 12 }, "+", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(2, true);
        }),
        new UITextPanel("X+", { 144, 136, 48, 48 }, { 12, 12 }, uiSymbols[2], BLACK, WHITE_L_80),
        new UIButton("X+", { 144, 200, 48, 48 }, { 12, 12 }, "-", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(2, false);
        }),

        // TEXT SYMBOL 4
        new UIButton("X+", { 216, 72, 48, 48 }, { 12, 12 }, "+", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(3, true);
        }),
        new UITextPanel("X+", { 216, 136, 48, 48 }, { 12, 12 }, uiSymbols[3], BLACK, WHITE_L_80),
        new UIButton("X+", { 216, 200, 48, 48 }, { 12, 12 }, "-", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(3, false);
        }),

        // TEXT SYMBOL 5
        new UIButton("X+", { 288, 72, 48, 48 }, { 12, 12 }, "+", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(4, true);
        }),
        new UITextPanel("X+", { 288, 136, 48, 48 }, { 12, 12 }, uiSymbols[4], BLACK, WHITE_L_80),
        new UIButton("X+", { 288, 200, 48, 48 }, { 12, 12 }, "-", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(4, false);
        }),

        // Separate symbol
        new UITextPanel("X+", { 360, 136, 48, 48 }, { 12, 12 }, separteSymbol, BLACK, WHITE_L_80),

        // TEXT SYMBOL 6
        new UIButton("X+", { 432, 72, 48, 48 }, { 12, 12 }, "+", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(5, true);
        }),
        new UITextPanel("X+", { 432, 136, 48, 48 }, { 12, 12 }, uiSymbols[5], BLACK, WHITE_L_80),
        new UIButton("X+", { 432, 200, 48, 48 }, { 12, 12 }, "-", BLACK, WHITE_L_80, WHITE_L_5, [] {
            SetSpeedButtonsPress(5, false);
        }),
        
        new UIButton("ENTER", { 0, 264, 480, 48 }, { 12, 12 }, ENTER, BLACK, WHITE_L_80, WHITE_L_5, []{}, [] { 
            EnterVSpeedInt();
            SaveVSpeedInt();
            PAGES::ChangePageFormName("MainPage");
        }),
        NULL,
    };

    SpeedControlPage(char* getName) {
        Name = getName;

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            UIObjects[i] = localObjects[i];
        }
    }

    void Awake() override {
        
    }

    void Start() override {
        if (VFirstLoad) {
            LoadVSpeedInt();
            VFirstLoad = !VFirstLoad;
        }

        RepaintAll();

        for (int i = 0; i < 6; i++)
            UpdateTextByIndex(i);
    }

    void Update() override {
        for (int i = 0; i < 6; i++) {
            if (lastUiInt[i] != VSpeed[i])
                UpdateTextByIndex(i);

            lastUiInt[i] = VSpeed[i];
        }

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }
    }

    void UpdateTextByIndex(int i) {
        uiSymbols[i].SetText(VSpeed[i]);
        RepaintTextByIndex(i);
    }

    void RepaintTextByIndex(int i) {
        if (i == 0) UIObjects[2]->Repaint();
        else if (i == 1) UIObjects[5]->Repaint();
        else if (i == 2) UIObjects[8]->Repaint();
        else if (i == 3) UIObjects[11]->Repaint();
        else if (i == 4) UIObjects[14]->Repaint();
        else if (i == 5) UIObjects[18]->Repaint();
    }
};

#endif