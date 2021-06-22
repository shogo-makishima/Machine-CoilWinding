#ifndef _TEXT_H_
#define _TEXT_H_

#include <avr/dtostrf.h>
#define MAX_TEXT_LENGHT 16

/// Класс текста
class Text {
    public: 
    /// Массив символов
    char text[MAX_TEXT_LENGHT];

    /// Базовый конструктор
    Text(char getText[MAX_TEXT_LENGHT]) {
        strcpy(text, getText);
    }

    /// Установить текст: char*
    void SetText(char* getText) { strcpy(text, getText); }
    
    /// Установить текст: int
    void SetText(int getText) { 
        char array[MAX_TEXT_LENGHT];
        itoa(getText, array, 10);
        strcpy(text, array);
    }

    /// Установить текст: float
    void SetText(float getText) { 
        char array[MAX_TEXT_LENGHT];
        dtostrf(getText, 6, 1, array);
        strcpy(text, array);
    }

    /// Установить текст: long
    void SetText(long getText) { 
        char array[MAX_TEXT_LENGHT];
        ltoa(getText, array, 10);
        strcpy(text, array);
    }

    /// Получить число: int
    int GetInt() { return atoi(text); }

    /// Получить число: float
    float GetFloat() { return atof(text); }
};

#endif

