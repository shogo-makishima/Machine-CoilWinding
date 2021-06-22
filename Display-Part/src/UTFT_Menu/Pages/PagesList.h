#ifndef _PAGES_LIST_H_
#define _PAGES_LIST_H_

#include "Page.h"
#include "LimitPage.h"
#include "MainPage.h"
#include "SettingsPage.h";
#include "SpeedPage.h"

/// Список страниц
Page* PAGES_LIST[MAX_PAGES] = {
    new Empty("Empty"),
    new MainPage("MainPage"),
    new LimitPage("LimitPage"),
    new SettingsPage("SettingsPage"),
    new SpeedPage("SpeedPage"),
    NULL,
};

/// Текущая старница
Page* currentPage = NULL;

#endif