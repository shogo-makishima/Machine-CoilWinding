// URTouch_ButtonTest 
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

// Объявление используемых шрифтов
extern uint8_t BigFont[];

int x, y;
char stCurrent[20]="";
int stCurrentLen=0;
char stLast[20]="";

/*********************************
**   Пользовательские функции   **
*********************************/

void drawButtons()
{
// Прорисовка верхнего ряда кнопок
  for (x=0; x<5; x++)
  {
    myGLCD.setColor(0, 0, 255);
    myGLCD.fillRoundRect (10+(x*60), 10, 60+(x*60), 60);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (10+(x*60), 10, 60+(x*60), 60);
    myGLCD.printNumI(x+1, 27+(x*60), 27);
  }
// Прорисовка цнтрального ряда кнопок
  for (x=0; x<5; x++)
  {
    myGLCD.setColor(0, 0, 255);
    myGLCD.fillRoundRect (10+(x*60), 70, 60+(x*60), 120);
    myGLCD.setColor(255, 255, 255);
    myGLCD.drawRoundRect (10+(x*60), 70, 60+(x*60), 120);
    if (x<4)
      myGLCD.printNumI(x+6, 27+(x*60), 87);
  }
  myGLCD.print("0", 267, 87);
// Прорисовка нижнего ряда кнопок
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (10, 130, 150, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (10, 130, 150, 180);
  myGLCD.print("Clear", 40, 147);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (160, 130, 300, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (160, 130, 300, 180);
  myGLCD.print("Enter", 190, 147);
  myGLCD.setBackColor (0, 0, 0);
}

void updateStr(int val)
{
  if (stCurrentLen<20)
  {
    stCurrent[stCurrentLen]=val;
    stCurrent[stCurrentLen+1]='\0';
    stCurrentLen++;
    myGLCD.setColor(0, 255, 0);
    myGLCD.print(stCurrent, LEFT, 224);
  }
  else
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.print("BUFFER FULL!", CENTER, 192);
    delay(500);
    myGLCD.print("            ", CENTER, 192);
    delay(500);
    myGLCD.print("BUFFER FULL!", CENTER, 192);
    delay(500);
    myGLCD.print("            ", CENTER, 192);
    myGLCD.setColor(0, 255, 0);
  }
}

// Прорисовка красной рамки вокруг нажатой кнопки
void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

/**************************
**  Необходимые функции  **
**************************/

void setup()
{
// Инициализация дисплея и TouchScreen с установкой начальных параметров
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  drawButtons();  
}

void loop()
{
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      
      if ((y>=10) && (y<=60))  // Если координата нажатия по оси Y соответствует верхнему ряду кнопок
      {
        if ((x>=10) && (x<=60))  // Кнопка: 1
        {
          waitForIt(10, 10, 60, 60);
          updateStr('1');
        }
        if ((x>=70) && (x<=120))  // Кнопка: 2
        {
          waitForIt(70, 10, 120, 60);
          updateStr('2');
        }
        if ((x>=130) && (x<=180))  // Кнопка: 3
        {
          waitForIt(130, 10, 180, 60);
          updateStr('3');
        }
        if ((x>=190) && (x<=240))  // Кнопка: 4
        {
          waitForIt(190, 10, 240, 60);
          updateStr('4');
        }
        if ((x>=250) && (x<=300))  // Кнопка: 5
        {
          waitForIt(250, 10, 300, 60);
          updateStr('5');
        }
      }

      if ((y>=70) && (y<=120))  // Если координата нажатия по оси Y соответствует центральному ряду кнопок
      {
        if ((x>=10) && (x<=60))  // Кнопка: 6
        {
          waitForIt(10, 70, 60, 120);
          updateStr('6');
        }
        if ((x>=70) && (x<=120))  // Кнопка: 7
        {
          waitForIt(70, 70, 120, 120);
          updateStr('7');
        }
        if ((x>=130) && (x<=180))  // Кнопка: 8
        {
          waitForIt(130, 70, 180, 120);
          updateStr('8');
        }
        if ((x>=190) && (x<=240))  // Кнопка: 9
        {
          waitForIt(190, 70, 240, 120);
          updateStr('9');
        }
        if ((x>=250) && (x<=300))  // Кнопка: 0
        {
          waitForIt(250, 70, 300, 120);
          updateStr('0');
        }
      }

      if ((y>=130) && (y<=180))  // Если координата нажатия по оси Y соответствует нижнему ряду кнопок
      {
        if ((x>=10) && (x<=150))  // Кнопка: Clear
        {
          waitForIt(10, 130, 150, 180);
          stCurrent[0]='\0';
          stCurrentLen=0;
          myGLCD.setColor(0, 0, 0);
          myGLCD.fillRect(0, 224, 319, 239);
        }
        if ((x>=160) && (x<=300))  // Кнопка: Enter
        {
          waitForIt(160, 130, 300, 180);
          if (stCurrentLen>0)
          {
            for (x=0; x<stCurrentLen+1; x++)
            {
              stLast[x]=stCurrent[x];
            }
            stCurrent[0]='\0';
            stCurrentLen=0;
            myGLCD.setColor(0, 0, 0);
            myGLCD.fillRect(0, 208, 319, 239);
            myGLCD.setColor(0, 255, 0);
            myGLCD.print(stLast, LEFT, 208);
          }
          else
          {
            myGLCD.setColor(255, 0, 0);
            myGLCD.print("BUFFER EMPTY", CENTER, 192);
            delay(500);
            myGLCD.print("            ", CENTER, 192);
            delay(500);
            myGLCD.print("BUFFER EMPTY", CENTER, 192);
            delay(500);
            myGLCD.print("            ", CENTER, 192);
            myGLCD.setColor(0, 255, 0);
          }
        }
      }
    }
  }
}

