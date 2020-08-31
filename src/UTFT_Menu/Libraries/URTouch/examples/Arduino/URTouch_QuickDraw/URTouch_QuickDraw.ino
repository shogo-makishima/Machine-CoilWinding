// URTouch_QuickDraw 
// Авторское право (C)2015 Rinky-Dink Electronics, Henning Karlsen. Все права защищены
// web: http://www.RinkyDinkElectronics.com/
//
// Эта программа является быстрой демонстрацией того, как можно использовать библиотеку.
// Для этой программы требуется библиотека UTFT.
// Предполагается, что Вы знаете, как изменить номера выводов дисплея и сенсорного экрана.

#include <UTFT.h>
#include <URTouch.h>

// Инициализация дисплея:
// ----------------------
// UTFT myGLCD(TFT395UNO,  A2,A1,A3,A4,A0);            // тип дисплея 3,95 UNO  (480x320 chip ILI9327)
// UTFT myGLCD(TFT32MEGA,  38,39,40,41   );            // тип дисплея 3,2  MEGA (480x320 chip ILI9481)
// UTFT myGLCD(TFT28UNO,   A2,A1,A3,A4,A0);            // тип дисплея 2,8  UNO  (320x240 chip ILI9341)
   UTFT myGLCD(TFT01_24SP,  5, 4, 8, 7, 6);            // тип дисплея 2,4  TFT  (240×320 chip ILI9341)
// UTFT myGLCD(TFT01_22SP,  5, 4, 8, 7, 6);            // тип дисплея 2,2  TFT  (320×240 chip ILI9340)
// UTFT myGLCD(TFT18SHLD,   5, 4, 8, 7, 6);            // тип дисплея 1,8  TFT  (128x160 chip ST7735S)
// UTFT myGLCD(ТИП_МОДЕЛИ, 19,18,17,16   );            // тип дисплея шилд UNO      - подходит для большинства стандартных дисплеев
// UTFT myGLCD(ТИП_МОДЕЛИ, 38,39,40,41   );            // тип дисплея шилд Mega/Due - подходит для большинства стандартных дисплеев
// UTFT myGLCD(ТИП_МОДЕЛИ, 25,26,27,28   );            // тип дисплея шилд Due      - CTE TFT LCD/SD
// UTFT myGLCD(ТИП_МОДЕЛИ, 22,23,31,33   );            // тип дисплея шилд Due      - ElecHouse TFT LCD/SD
// UTFT myGLCD(ТИП_МОДЕЛИ, 23,22, 3, 4   );            // тип дисплея               - Teensy 3.x TFT Test Board

// Инициализация touchscreen:
// --------------------------
   URTouch  myTouch(13,12,11,10, 9);                   // дисплей 2,4 TFT 240×320
// URTouch  myTouch(15,10,14, 9, 8);                   // подходит для большинства стандартных шилдов под Arduino Uno/2009
// URTouch  myTouch( 6, 5, 4, 3, 2);                   // подходит для большинства стандартных шилдов под Arduino Mega/Due
// URTouch  myTouch( 6, 5, 4, 3, 2);                   // шилд CTE TFT LCD/SD под Arduino Due
// URTouch  myTouch(26,31,27,28,29);                   // Teensy 3.x TFT Test Board
// URTouch  myTouch(25,26,27,29,30);                   // шилд ElecHouse TFT LCD/SD под Arduino Due

void setup()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
}

void loop()
{
  long x, y;
  
  while (myTouch.dataAvailable() == true)
  {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    if ((x!=-1) and (y!=-1))
    {
      myGLCD.drawPixel (x, y);
    }
  }
}

