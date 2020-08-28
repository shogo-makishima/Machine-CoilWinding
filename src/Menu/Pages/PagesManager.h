#ifndef _PAGES_MANAGER_H_
#define _PAGES_MANAGER_H_

#include "Page.h"

class PagesManager {
    public:
    Page* Pages[MAX_PAGES] = {
        new MainPage("MainPage"),
        new SimplePage("SimplePage"),
        NULL,
    };

    Page* page = NULL;

    void PagesAwake() {
        for (int i = 0; i < MAX_PAGES; i++) {
            if (Pages[i] == NULL) break;
            Pages[i]->Awake();
            // Serial.println(String(Pages[i]->Name) + " == " + String(name) + ": " + ((strcmp(Pages[i]->Name, name) == 0) ? "true" : "false"));
        }
    }

    void ChangePageFormName(const char* name) {
        for (int i = 0; i < MAX_PAGES; i++) {
            if (Pages[i] == NULL) break;
            else if (strcmp(Pages[i]->Name, name) == 0) { 
                page = Pages[i];
                break;
            }
            
            // Serial.println(String(Pages[i]->Name) + " == " + String(name) + ": " + ((strcmp(Pages[i]->Name, name) == 0) ? "true" : "false"));
        }
        
        if (page != NULL) page->Start();
    }

    void UpdateCurrentPage() {
        if (page != NULL) page->Update();
    }
};

#endif