#ifndef _SETTINGS_PAGE_H_
#define _SETTINGS_PAGE_H_

#include "PagesManager.h"
#include "UTFT_Menu/Menus.h"

class SettingsPage : public Page {
    private:
    Text manageSaves_Text = { MANAGE_SAVES };

    public:
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        new UITextPanel("ManageSaves", { 0, 0, 180, 50 }, { 12, 30 }, manageSaves_Text, BLACK, WHITE_L_80),
        new UIButton("Save", { 190, 0, 90, 50 }, { 12, 30 }, SAVE, BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            Serial1.println("M12");
        }),
        new UIButton("Load", { 290, 0, 90, 50 }, { 12, 30 }, LOAD, BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            Serial1.println("M13");
        }),
        new UIButton("Clear", { 390, 0, 90, 50 }, { 12, 30 }, CLEAR, BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            
        }),

        new UIButton("Apply", { 170, 246, 140, 50 }, { 12, 30 }, APPLY, BLACK, WHITE_L_80, WHITE_L_5, []{}, [&, this] {
            PAGES::ChangePageFormName("MainPage");
        }),
        NULL,
    };

    SettingsPage(char* getName) {
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