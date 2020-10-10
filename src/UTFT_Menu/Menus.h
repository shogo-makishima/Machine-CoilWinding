#pragma once

// #include "Libraries/UTFT/UTFT.h"
// #include "Libraries/URTouch/URTouch.h"

#include "platform.h"

#undef min
#undef max

#include "functional"

#include "SPI.h"
#include "Libraries/Adafruit_GFX/Adafruit_GFX.h"
#include "Libraries/Waveshare_ILI9486/Waveshare_ILI9486.h"

extern uint8_t SmallFont[];                            // подключаем маленький шрифт
extern uint8_t BigFont[];                              // подключаем большой шрифт
extern uint8_t SevenSegNumFont[];                      // подключаем цифровой шрифт


static Waveshare_ILI9486 GLCD;
// static URTouch TOUCH(6, 5, 4, 3, 2);

#include "Pages/Variables.h"

#include "UI/UISettings.hpp"

#include "Utilites/ArraysTools.h"
#include "Utilites/Math.hpp"
#include "Utilites/Timer.h"
#include "Utilites/TouchEmulator.hpp"

static TouchEmulator TOUCH = TouchEmulator();

#include "UI/Rect.h"
#include "UI/Vector2D.h"
#include "UI/Text.h"

#include "UI/Colors.h"

#include "UI/UIObject.h"
#include "UI/UIPanel.hpp"
#include "UI/UIButton.hpp"
#include "UI/UITextPanel.hpp"
#include "UI/UICheckBox.h"

#include "CoilWinding/CoilWinding.hpp"

#include "Pages/Page.h"

#include "Pages/PagesManager.h"

#include "Pages/PagesList.h"


static void INIT() {
    Serial.begin(9600);
    Serial.println(TUTORIAL);

    SPI.begin();
  	GLCD.begin();

    GLCD.resetTsConfigData();
    GLCD.setRotation(1);

    TOUCH.InitTouch();
    TOUCH.setPrecision(0);

    PAGES::Init(PAGES_LIST);
    PAGES::ChangePageFormName("MainPage");

    CoilWinding::Init();
}
