#ifndef _MENU_ABSTRACT_H_
#define _MENU_ABSTRACT_H_

#include "UTFT_Menu/Menus.h"

/// Основной класс страницы
class Page {
    public:
    /// Название меню
    char Name[32];

    /// Список объектов
    UIObject* UIObjects[MAX_OBJECTS_ON_PAGE];

    /// Функция пробуждения
    virtual void Awake();
    /// Функция старта
    virtual void Start();
    /// Функция обновления
    virtual void Update();
    
    /// Получить ссылку на элемент интерфейса по имени
    UIObject* GetObjectByName(char* name) {
        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            if (strcmp(UIObjects[i]->Name, name) == 0) return UIObjects[i];
        }

        return NULL;
    }

    /// Перерисовать элемент по его индексу
    void RepaintByIndex(int index) {
        if (UIObjects[index] == NULL) return;
        UIObjects[index]->Repaint();
    }

    /// Перерисовать всё
    void RepaintAll() {
        GLCD.fillScreen(BACKGDOUND);

        for (int i = 0; i < MAX_OBJECTS_ON_PAGE; i++) {
            if (UIObjects[i] == NULL) break;
            UIObjects[i]->Repaint();
        }
    }
};

/// Пустая страница
class Empty : public Page {
    private:

    public:
    /// Костыль локальные объекты
    UIObject* localObjects[MAX_OBJECTS_ON_PAGE] = {
        NULL,
    };

    /// Базовый конструктор
    Empty(char* getName) {
        strcpy(Name, getName);
        
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