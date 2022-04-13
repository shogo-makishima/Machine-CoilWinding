#ifndef _SPEED_PAGE_H_
#define _SPEED_PAGE_H_


#include "PagesManager.h"
#include "UTFT_Menu/Menus.h"

#define MAX_SPEED_CONFIG_0 1

class SpeedPage : public Page {
    private:
    int last_speedUI[SPEED_LIST_LENGHT] = {  0, 0, 0, 0 };

    Text uiSymbols[SPEED_LIST_LENGHT] = { 
        { "0" },
        { "0" },
        { "0" },
        { "0" },
    };

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UIButton("ENTER", { 0, 264, 230, 50 }, { 12, 30 }, ENTER, BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            Serial1.print("M32 ");
            localSpeed = VariableController::SpeedToInt();
            Serial1.println(localSpeed);
            Serial1.println("M12");
            
            PAGES::ChangePageFormName("MainPage");
        }),

        // TEXT SYMBOL 1
        new UIButton("X+", { 81, 10, 75, 75 }, { 25, 47 }, "+", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(0, true);
        }, &FREE_SANS_24PT),
        new UITextPanel("X+", { 81, 90, 75, 75 }, { 25, 52 }, uiSymbols[0], BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UIButton("X+", { 81, 170, 75, 75 }, { 25, 47 }, "-", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(0, false);
        }, &FREE_SANS_24PT),

        // TEXT SYMBOL 2
        new UIButton("X+", { 162, 10, 75, 75 }, { 25, 47 }, "+", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(1, true);
        }, &FREE_SANS_24PT),
        new UITextPanel("X+", { 162, 90, 75, 75 }, { 25, 52 }, uiSymbols[1], BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UIButton("X+", { 162, 170, 75, 75 }, { 25, 47 }, "-", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(1, false);
        }, &FREE_SANS_24PT),

        // TEXT SYMBOL 3
        new UIButton("X+", { 243, 10, 75, 75 }, { 25, 47 }, "+", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(2, true);
        }, &FREE_SANS_24PT),
        new UITextPanel("X+", { 243, 90, 75, 75 }, { 25, 52 }, uiSymbols[2], BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UIButton("X+", { 243, 170, 75, 75 }, { 25, 47 }, "-", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(2, false);
        }, &FREE_SANS_24PT),

        // TEXT SYMBOL 4
        new UIButton("X+", { 324, 10, 75, 75 }, { 25, 47 }, "+", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(3, true);
        }, &FREE_SANS_24PT),
        new UITextPanel("X+", { 324, 90, 75, 75 }, { 25, 52 }, uiSymbols[3], BLACK, WHITE_L_80, &FREE_SANS_24PT),
        new UIButton("X+", { 324, 170, 75, 75 }, { 25, 47 }, "-", BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            SetSpeedButtonsPress(3, false);
        }, &FREE_SANS_24PT),
        
        new UIButton("CLEAR", { 270, 264, 230, 50 }, { 12, 30 }, CLEAR, BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            VariableController::ClearLimit();
        }),
        NULL,
    };

    SpeedPage(char* getName) {
        strcpy(Name, getName);

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            UIObjects[i] = localObjects[i];
        }
    }

    void Awake() override {
        
    }

    void Start() override {
        for (int i = 0; i < SPEED_LIST_LENGHT; i++) SetTextByIndex(i);

        RepaintAll();
    }

    void Update() override {
        for (int i = 0; i < SPEED_LIST_LENGHT; i++) {
            if (last_speedUI[i] != localSpeedMenu[i])
                UpdateTextByIndex(i);

            last_speedUI[i] = localSpeedMenu[i];
        }

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }

        // localCanMove = false;
    }

    void SetSpeedButtonsPress(int index, bool direction) {
        localSpeedMenu[index] = localSpeedMenu[index] + (1 * ((direction) ? 1 : -1));
        if (index == 0) {
            localSpeedMenu[index] = Math::CycleClamp(0, MAX_SPEED_CONFIG_0, localSpeedMenu[index]);
            if (localSpeedMenu[index] == MAX_SPEED_CONFIG_0) {
                for (int i = 1; i < SPEED_LIST_LENGHT; i++)
                    localSpeedMenu[i] = 0;
            }
        } else if (index != 0 && localSpeedMenu[0] == MAX_SPEED_CONFIG_0) localSpeedMenu[index] = 0; 
        else localSpeedMenu[index] = Math::CycleClamp(0, 9, localSpeedMenu[index]);
    }

    void UpdateTextByIndex(int i) {
        SetTextByIndex(i);
        RepaintTextByIndex(i);
    }   

    void SetTextByIndex(int i) {
        uiSymbols[i].SetText(localSpeedMenu[i]);
    }

    void RepaintTextByIndex(int i) {
        if (i == 0) UIObjects[2]->Repaint();
        else if (i == 1) UIObjects[5]->Repaint();
        else if (i == 2) UIObjects[8]->Repaint();
        else if (i == 3) UIObjects[11]->Repaint();
    }
};


#endif