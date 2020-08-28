#ifndef _MENU_ABSTRACT_H_
#define _MENU_ABSTRACT_H_

#include "Menu/Menus.h"

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

class MainPage : public Page {
    private:
    int lastCounter = -1;

    Text uiPanelText = { "0" };

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UIButton("X-", { 0, 5, 115, 115 }, { 25, 25 }, "X-", BLACK, WHITE_L_80, WHITE_L_5, [] {
            ChangeCounter(false);
        }),
        new UITextPanel("X+", { 125, 5, 225, 115 }, { 25, 25 }, uiPanelText, BLACK, WHITE_L_80),
        new UIButton("X+", { 360, 5, 115, 115 }, { 25, 25 }, "X+", BLACK, WHITE_L_80, WHITE_L_5, [] {
            ChangeCounter(true);
        }),

        new UIPanel("Y+", { 0, 130, 115, 115 }, BLUE),
        new UIPanel("Y-", { 360, 130, 115, 115 }, BLUE),
        new UIPanel("Text", { 125, 130, 225, 115 }, BLUE),
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
        UpdateText();
    }

    void Update() override {
        if (lastCounter != Counter) UpdateText();

        lastCounter = Counter;

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Update();
        }
    }

    void UpdateText() {
        uiPanelText.SetText(Counter);
        UIObjects[2]->Repaint();
    }
};

class SimplePage : public Page {
    private:
    Text uiSymbol_1 = { "0" };

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UIButton("X+", { 0, 0, 65, 65 }, { 25, 25 }, "↑", BLACK, WHITE_L_80, WHITE_L_5),
        new UITextPanel("X+", { 0, 75, 65, 65 }, { 25, 25 }, uiSymbol_1, BLACK, WHITE_L_80),
        new UIButton("X+", { 0, 145, 65, 65 }, { 25, 25 }, "↓", BLACK, WHITE_L_80, WHITE_L_5),
        NULL,
    };

    SimplePage(char* getName) {
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