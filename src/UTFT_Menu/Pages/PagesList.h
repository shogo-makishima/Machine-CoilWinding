#ifndef _PAGES_LIST_H_
#define _PAGES_LIST_H_

#include "Page.h"
#include "SpeedControlPage.h"
#include "MainPage.h"

Page* PAGES_LIST[MAX_PAGES] = {
    new Empty("Empty"),
    new MainPage("MainPage"),
    new SpeedControlPage("SpeedControlPage"),
    NULL,
};

Page* currentPage = NULL;

#endif