#ifndef _UISETTINGS_H_
#define _UISETTINGS_H_

#include "Colors.h"

#define MAX_OBJECTS_ON_PAGE 32
#define MAX_PAGES 8

#define BACKGDOUND BLACK

#include "UTFT_Menu/Libraries/Adafruit_GFX/Fonts/FreeSans12pt7b.h"
#define DEFAULT_FONT FreeSans12pt7b

#include "UTFT_Menu/Libraries/Adafruit_GFX/Fonts/FreeSans24pt7b.h"
#define FREE_SANS_24PT FreeSans24pt7b

/// Строки

#define ENTER         "Enter"
#define CLEAR         "Clear"
#define SPEED         "Speed"
#define RUN_OR_STOP   "Run || Stop"
#define MODE          "Mode"
#define DIRECTION     "+ | -"
#define SAVE          "Save"
#define LOAD          "Load"
#define APPLY         "Apply"
#define SETTINGS      "Settings"
#define MANAGE_SAVES  "Manage saves"

#define TUTORIAL "<----------->\nCommands:\n1. t X Y - эмуляция touchsreen'а.\n2. c N - сменить меню по его названию.\n<----------->\n\n"

#endif