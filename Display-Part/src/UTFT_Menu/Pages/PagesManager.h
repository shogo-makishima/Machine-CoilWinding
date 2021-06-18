#ifndef _PAGES_MANAGER_H_
#define _PAGES_MANAGER_H_

#include "Page.h"

/// Страницы
namespace PAGES {
    /// Список страниц
    Page* Pages[MAX_PAGES] = {
        NULL,
    };

    /// Текущая старница
    Page* page = NULL;
    /// Имя предыдущей страницы
    char lastPageName[32] = "MainPage";

    /// Создание    
    void Init(Page** getPages) {
        for (int i = 0; i < MAX_PAGES; i++)
            Pages[i] = getPages[i];
    }

    /// Метод вызывающий функию Awake() на всех страницах
    void PagesAwake() {
        for (int i = 0; i < MAX_PAGES; i++) {
            if (Pages[i] == NULL) break;
            Pages[i]->Awake();
            // Serial.println(String(Pages[i]->Name) + " == " + String(name) + ": " + ((strcmp(Pages[i]->Name, name) == 0) ? "true" : "false"));
        }
    }

    /// Поменять страницу по её имени
    void ChangePageFormName(const char* name) {
        for (int i = 0; i < MAX_PAGES; i++) {
            if (Pages[i] == NULL) break;
            else if (strcmp(Pages[i]->Name, name) == 0) {
                strcpy(lastPageName, page->Name); 
                page = Pages[i];
                Serial.println(lastPageName);
                break;
            }
            
            // Serial.println(String(Pages[i]->Name) + " == " + String(name) + ": " + ((strcmp(Pages[i]->Name, name) == 0) ? "true" : "false"));
        }
        
        if (page != NULL) page->Start();
    }

    /// Обновить текущую страницу
    void UpdateCurrentPage() {
        if (page != NULL) page->Update();
    }
}

#endif