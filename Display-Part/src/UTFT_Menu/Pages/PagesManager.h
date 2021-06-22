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
        }
    }

    /// Поменять страницу по её имени
    void ChangePageFormName(const char* name) {
        for (int i = 0; i < MAX_PAGES; i++) {
            if (Pages[i] == NULL) break;
            else if (strcmp(Pages[i]->Name, name) == 0) {
                TOUCH.b_canReadTouch = false;
                TOUCH.deathTimer.Reset();
                page = Pages[i];
                break;
            }
        }
        
        if (page != NULL) page->Start();
    }

    /// Обновить текущую страницу
    void UpdateCurrentPage() {
        if (page != NULL) page->Update();
    }
}

#endif