#include <Arduino.h>
#include <Scheduler/src/Scheduler.h>
#include "UTFT_Menu/Menus.h"

Timer updateTimer = Timer(10, [] {
    PAGES::UpdateCurrentPage();
});

void loopMotor() {
    CoilWinding::Update();
    delay(PAUSE);
    yield();
}

void setup() {
    

    INIT();
    
    Scheduler.startLoop(loopMotor);
}

void loop() {
    updateTimer.Update();
    TOUCH.Update();
    delay(10);
}


/*

#include <Stepper/src/Stepper.h> // Подключение библиотеки для работы с ШД

#include "AccelStepper/src/AccelStepper.h"
#include "AccelStepper/src/MultiStepper.h"

#define STEPS 200 // Количество шагов на один оборот
#define SPEED 200
#define PAUSE 10

// Создание экземпляра класса для работы с ШД. казываем кол-во шагов на один оборот
// и пины Arduino, к которым подключены обмотки двигатедя
AccelStepper engine_1(AccelStepper::FULL4WIRE, 11, 10, 9, 8);
AccelStepper engine_2(AccelStepper::FULL4WIRE, 7, 6, 5, 4);

// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepper engines;

long positions[2] = { 0, 0 };

void setup() {
    Serial.begin(9600);

    engine_1.setMaxSpeed(SPEED); // Устанавливаем скорость вращения об./мин.
    engine_2.setMaxSpeed(SPEED); // Устанавливаем скорость вращения об./мин.

    engines.addStepper(engine_1);
    engines.addStepper(engine_2);
}

void loop() {
    Serial.println(positions[0] / STEPS);

    positions[0] = STEPS; positions[1] = STEPS;

    engines.move(positions);
    engines.runSpeedToPosition();

    delay(PAUSE); // Ждём одну секунду
}

*/
/*
#include "UTFT_Menu/Menus.h"

Timer updateTimer = Timer(10, [] {
    PAGES::UpdateCurrentPage();
});

void setup() {
    Serial.begin(9600);
    Serial.println(TUTORIAL);

    PAGES::Init(PAGES_LIST);

  	GLCD.InitLCD();                                    // инициируем дисплей (в качестве параметра данной функции можно указать ориентацию дисплея: PORTRAIT или LANDSCAPE), по умолчанию LANDSCAPE - горизонтальная ориентация
    
    TOUCH.InitTouch();
    TOUCH.setPrecision(PREC_MEDIUM);

    PAGES::ChangePageFormName("MainPage");
}

void loop() {
    updateTimer.Update();
    TOUCH.Update();

    if (Serial.available()) {
        String command = Serial.readString();
        command[command.length() - 1] = '\0';

        Serial.println(command);

        if (command[0] == 'c') {
            command = command.substring(2);

            PAGES::ChangePageFormName(command.c_str());
            Serial.println("[PAGE] " + String(PAGES::page->Name) + " " + command);
        } else if (command[0] == 't') {
            command = command.substring(2);

            TOUCH.ParseTouch(command);
            Serial.println("[TOUCH] " + String(TOUCH.getX()) + " " + String(TOUCH.getY()) + " " + command);
        }
        
    }

    // testTimer.Update();

    // Serial.println(String(TOUCH.getX()) + ", " + String(TOUCH.getY()));
}
*/

/*
int counter = 0;
Rect testRect = { 0, 0, 50, 50 };

UIPanel panel = { "Panel", { 100, 0, 50, 50 }, VGA_FUCHSIA };

void FillTextRect(Rect rect) {
    counter++;
    // if (counter > 9) counter = 0;

    GLCD.setColor(BLACK);
    GLCD.fillRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);

    GLCD.setColor(WHITE);
    GLCD.setFont(SevenSegNumFont);
    GLCD.printNumI(counter, testRect.x, testRect.y);
}

Timer testTimer = Timer(1000, [] {
    FillTextRect(testRect);
});
*/

/*

#include "Adafruit_GFX/Adafruit_GFX.h" // Hardware-specific library
#include "MCUFRIEND_kbv/MCUFRIEND_kbv.h"

MCUFRIEND_kbv tft;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    tft.reset();
    uint16_t identifier = tft.readID();
    Serial.print("ID = 0x");
    Serial.println(identifier, HEX);

    if (identifier == 0xEFEF) identifier = 0x9486;
    else if (identifier == 0xD3D3) identifier = 0x9090;

    tft.begin(identifier);
    //  tft.fillScreen(BLACK);
}

char *msg[] = { "PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV" };
uint8_t aspect;

void loop() {
    // put your main code here, to run repeatedly:
    uint16_t x = 50, y = 100;
    tft.setRotation(aspect);
    tft.fillScreen(0x0000);
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.println(msg[aspect]);
    tft.setCursor(x, y);
    tft.println("[x=" + String(x) + ",y=" + String(y) + "]");
    delay(5000);
    tft.println("INVERT ON");
    tft.invertDisplay(true);
    delay(1000);
    tft.invertDisplay(false);
    tft.println("INVERT OFF");
    delay(1000);
    if (++aspect >= 4) aspect = 0;
}

*/