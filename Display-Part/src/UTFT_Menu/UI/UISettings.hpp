#ifndef _UISETTINGS_H_
#define _UISETTINGS_H_

#include "Colors.h"

#define MAX_OBJECTS_ON_PAGE 32
#define MAX_PAGES 8

#define BACKGDOUND BLACK

#define LANGUAGE 0

#if LANGUAGE == 0
    #include "UTFT_Menu/Libraries/Adafruit_GFX/Fonts/FreeSans12pt7b.h"
    #define DEFAULT_FONT FreeSans12pt7b

    #include "UTFT_Menu/Libraries/Adafruit_GFX/Fonts/FreeSans24pt7b.h"
    #define FREE_SANS_24PT FreeSans24pt7b

    #define ENTER         "Enter"
    #define CLEAR         "Clear"
    #define SPEED         "Limit"
    #define RUN_OR_STOP   "Run || Stop"
    #define MODE          "Mode"
    #define DIRECTION     "+ | -"
    #define SAVE          "Save"
    #define LOAD          "Load"
    #define APPLY         "Apply"
    #define SETTINGS      "Settings"
    #define MANAGE_SAVES  "Manage saves"
#endif
#if LANGUAGE == 1
    #include "UTFT_Menu/Libraries/Adafruit_GFX/FontsRus/FreeSans14.h"
    #define DEFAULT_FONT FreeSans14pt8b

    #include "UTFT_Menu/Libraries/Adafruit_GFX/FontsRus/FreeSansBold18.h"
    #define FREE_SANS_24PT FreeSansBold18pt8b

    #define ENTER         "Принять"
    #define CLEAR         "Очистить"
    #define SPEED         "Ограничения"
    #define RUN_OR_STOP   "Пауза"
    #define MODE          "Режим"
    #define DIRECTION     "Направление"
    #define SAVE          "Сохранить"
    #define LOAD          "Загрузить"
    #define APPLY         "Принять"
    #define SETTINGS      "Настройки"
    #define MANAGE_SAVES  "Сохранение"
#endif

#endif