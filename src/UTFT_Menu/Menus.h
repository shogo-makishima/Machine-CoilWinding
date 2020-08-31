#pragma once

#include "Libraries/UTFT/UTFT.h"
#include "Libraries/URTouch/URTouch.h"

extern uint8_t SmallFont[];                            // подключаем маленький шрифт
extern uint8_t BigFont[];                              // подключаем большой шрифт
extern uint8_t SevenSegNumFont[];                      // подключаем цифровой шрифт

static UTFT GLCD(TFT32MEGA_2, 38,39,40,41);                   // тип дисплея 3,2  MEGA (480x320 chip HX8357C)
// static URTouch TOUCH(6, 5, 4, 3, 2);

#include "Pages/Variables.h"
#include "UI/UISettings.hpp"
#include "Utilites/ArraysTools.h"
#include "Utilites/TouchEmulator.hpp"
static TouchEmulator TOUCH = TouchEmulator();

#include "Utilites/Math.hpp"

#include "Utilites/Timer.h"
#include "UI/Rect.h"
#include "UI/Vector2D.h"
#include "UI/Text.h"

#include "UI/Colors.h"

#include "UI/UIObject.h"
#include "UI/UIPanel.hpp"
#include "UI/UIButton.hpp"
#include "UI/UITextPanel.hpp"

#include "Pages/Page.h"

#include "Pages/PagesManager.h"

#include "Pages/PagesList.h"

// static PagesManager PAGES = PagesManager();

