#ifndef _PAGES_LIST_H_
#define _PAGES_LIST_H_

#include "Page.h"
#include "SpeedControlPage.h"
#include "MainPage.h"

/// Список страниц
Page* PAGES_LIST[MAX_PAGES] = {
    new Empty("Empty"),
    new MainPage("MainPage"),
    new SpeedControlPage("SpeedControlPage"),
    NULL,
};

/// Текущая старница
Page* currentPage = NULL;

#endif