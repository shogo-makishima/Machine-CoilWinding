// URTouch_QuickPaint 
// Авторское право (C)2015 Rinky-Dink Electronics, Henning Karlsen. Все права защищены
// web: http://www.RinkyDinkElectronics.com/
//
// Эта программа является быстрой демонстрацией того, как можно использовать библиотеку.
// Для этой программы требуется библиотека UTFT и дисплей с разрешением не менее 320x240.
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


// Объявление используемых шрифтов
extern uint8_t BigFont[];

int color = 0;
word colorlist[] = {VGA_WHITE, VGA_BLACK, VGA_RED, VGA_BLUE, VGA_GREEN, VGA_FUCHSIA, VGA_YELLOW, VGA_AQUA};
int  bsize = 4;

void drawColorMarkerAndBrushSize(int col)
{
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRect(25, 0, 31, 239);
  myGLCD.fillRect(myGLCD.getDisplayXSize()-31, 161, myGLCD.getDisplayXSize()-1, 191);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawPixel(25, (col*30)+15);
  for (int i=1; i<7; i++)
    myGLCD.drawLine(25+i, ((col*30)+15)-i, 25+i, ((col*30)+15)+i);
  
  if (color==1)
    myGLCD.setColor(VGA_WHITE);
  else
    myGLCD.setColor(colorlist[col]);
  if (bsize==1)
    myGLCD.drawPixel(myGLCD.getDisplayXSize()-15, 177);
  else
    myGLCD.fillCircle(myGLCD.getDisplayXSize()-15, 177, bsize);
    
  myGLCD.setColor(colorlist[col]);
}

void setup()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_HI);
  
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawLine(32,0,32,myGLCD.getDisplayYSize()-1);
  myGLCD.drawLine(myGLCD.getDisplayXSize()-32,0,myGLCD.getDisplayXSize()-32,myGLCD.getDisplayYSize()-1);
  myGLCD.print("C", myGLCD.getDisplayXSize()-24, 8);
  myGLCD.print("L", myGLCD.getDisplayXSize()-24, 24);
  myGLCD.print("E", myGLCD.getDisplayXSize()-24, 40);
  myGLCD.print("A", myGLCD.getDisplayXSize()-24, 56);
  myGLCD.print("R", myGLCD.getDisplayXSize()-24, 72);
  myGLCD.print("+", myGLCD.getDisplayXSize()-24, 136);
  myGLCD.print("-", myGLCD.getDisplayXSize()-24, 200);
  myGLCD.fillRect(myGLCD.getDisplayXSize()-32,96,myGLCD.getDisplayXSize()-1,128);
  myGLCD.drawLine(myGLCD.getDisplayXSize()-32,160,myGLCD.getDisplayXSize()-1,160);
  myGLCD.drawLine(myGLCD.getDisplayXSize()-32,192,myGLCD.getDisplayXSize()-1,192);
  myGLCD.drawLine(myGLCD.getDisplayXSize()-32,224,myGLCD.getDisplayXSize()-1,224);
  for (int i=0; i<8; i++)
  {
    myGLCD.setColor(colorlist[i]);
    myGLCD.fillRect(0, (i*30), 24, (((i+1)*30)-1));
  }
  drawColorMarkerAndBrushSize(color);
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
      if (x>(31+bsize) and (x<myGLCD.getDisplayXSize()-(31+bsize)))
      {
        if (bsize==1)
          myGLCD.drawPixel(x, y);
        else
          myGLCD.fillCircle(x, y, bsize);
      }
      else
      {
        if (x<(30+bsize))
        {
          if (y<240)
          {
            color = y / 30;
            drawColorMarkerAndBrushSize(color);
            while (myTouch.dataAvailable()) {};
            delay(50);
         }
        }
        else
        {
          if (y<96)
          {
            myGLCD.setColor(VGA_BLACK);
            myGLCD.fillRect(33, 0, myGLCD.getDisplayXSize()-33, myGLCD.getDisplayYSize()-1);
            myGLCD.setColor(colorlist[color]);
          }
          if ((y>128) and (y<160))
          {
            if (bsize<7)
            {
              bsize++;
              drawColorMarkerAndBrushSize(color);
              while (myTouch.dataAvailable()) {};
              delay(50);
            }
          }
          if ((y>160) and (y<192))
          {
              bsize=4;
              drawColorMarkerAndBrushSize(color);
              while (myTouch.dataAvailable()) {};
              delay(50);
          }
          if ((y>192) and (y<224))
          {
            if (bsize>1)
            {
              bsize--;
              drawColorMarkerAndBrushSize(color);
              while (myTouch.dataAvailable()) {};
              delay(50);
            }
          }
        }
      }
    }
  }
}
