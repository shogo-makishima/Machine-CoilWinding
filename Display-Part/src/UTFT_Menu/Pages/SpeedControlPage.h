#ifndef _SIMPLEPAGE_H_
#define _SIMPLEPAGE_H_

#include "PagesManager.h"
#include "UTFT_Menu/Menus.h"

class SpeedControlPage : public Page {
    private:
    int last_limitUI[LIMIT_LIST_LENGHT] = {  0, 0, 0, 0, 0 };

    Text uiSymbols[LIMIT_LIST_LENGHT] = { 
        { "0" },
        { "0" },
        { "0" },
        { "0" },
        { "0" },
    };

    Text separteSymbol = { "." };

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UIButton("ENTER", { 0, 264, 230, 50 }, { 12, 30 }, ENTER, BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            Serial1.print("M30 ");
            Serial1.println(VariableController::LimitToFloat() * 10);
            Serial1.println("M12");
            localLimit = VariableController::LimitToFloat();
            PAGES::ChangePageFormName("MainPage");
        }),

        // TEXT SYMBOL 1
        new UIButton("X+", { 0, 10, 75, 75 }, { 25, 47 }, "+", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(0, true);
        }, &FREE_SANS_24PT),
        new UITextPanel("X+", { 0, 90, 75, 75 }, { 25, 52 }, uiSymbols[0], BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UIButton("X+", { 0, 170, 75, 75 }, { 25, 47 }, "-", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(0, false);
        }, &FREE_SANS_24PT),

        // TEXT SYMBOL 2
        new UIButton("X+", { 81, 10, 75, 75 }, { 25, 47 }, "+", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(1, true);
        }, &FREE_SANS_24PT),
        new UITextPanel("X+", { 81, 90, 75, 75 }, { 25, 52 }, uiSymbols[1], BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UIButton("X+", { 81, 170, 75, 75 }, { 25, 47 }, "-", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(1, false);
        }, &FREE_SANS_24PT),

        // TEXT SYMBOL 3
        new UIButton("X+", { 162, 10, 75, 75 }, { 25, 47 }, "+", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(2, true);
        }, &FREE_SANS_24PT),
        new UITextPanel("X+", { 162, 90, 75, 75 }, { 25, 52 }, uiSymbols[2], BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UIButton("X+", { 162, 170, 75, 75 }, { 25, 47 }, "-", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(2, false);
        }, &FREE_SANS_24PT),

        // TEXT SYMBOL 4
        new UIButton("X+", { 243, 10, 75, 75 }, { 25, 47 }, "+", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(3, true);
        }, &FREE_SANS_24PT),
        new UITextPanel("X+", { 243, 90, 75, 75 }, { 25, 52 }, uiSymbols[3], BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UIButton("X+", { 243, 170, 75, 75 }, { 25, 47 }, "-", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(3, false);
        }, &FREE_SANS_24PT),

        // TEXT SYMBOL 5
        new UIButton("X+", { 405, 10, 75, 75 }, { 25, 47 }, "+", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(4, true);
        }, &FREE_SANS_24PT),
        new UITextPanel("X+", { 405, 90, 75, 75 }, { 25, 52 }, uiSymbols[4], BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UIButton("X+", { 405, 170, 75, 75 }, { 25, 47 }, "-", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(4, false);
        }, &FREE_SANS_24PT),

        // Separate symbol
        new UITextPanel("X+", { 324, 90, 75, 75 }, { 25, 52 }, separteSymbol, BLACK, WHITE_L_80, &FREE_SANS_24PT),
        
        new UIButton("CLEAR", { 270, 264, 230, 50 }, { 12, 30 }, CLEAR, BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            VariableController::ClearLimit();
        }),
        NULL,
    };

    SpeedControlPage(char* getName) {
        strcpy(Name, getName);

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            UIObjects[i] = localObjects[i];
        }
    }

    void Awake() override {
        
    }

    void Start() override {
        for (int i = 0; i < LIMIT_LIST_LENGHT; i++) SetTextByIndex(i);

        RepaintAll();
    }

    void Update() override {
        for (int i = 0; i < LIMIT_LIST_LENGHT; i++) {
            if (last_limitUI[i] != localLimitMenu[i])
                UpdateTextByIndex(i);

            last_limitUI[i] = localLimitMenu[i];
        }

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }

        // localCanMove = false;
    }

    void SetSpeedButtonsPress(int index, bool direction) {
        localLimitMenu[index] = localLimitMenu[index] + (1 * ((direction) ? 1 : -1));
        localLimitMenu[index] = Math::CycleClamp(0, 9, localLimitMenu[index]);
    }

    void UpdateTextByIndex(int i) {
        SetTextByIndex(i);
        RepaintTextByIndex(i);
    }   

    void SetTextByIndex(int i) {
        uiSymbols[i].SetText(localLimitMenu[i]);
    }

    void RepaintTextByIndex(int i) {
        if (i == 0) UIObjects[2]->Repaint();
        else if (i == 1) UIObjects[5]->Repaint();
        else if (i == 2) UIObjects[8]->Repaint();
        else if (i == 3) UIObjects[11]->Repaint();
        else if (i == 4) UIObjects[14]->Repaint();
    }
};

#endif