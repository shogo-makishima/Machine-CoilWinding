#ifndef _TEXT_H_
#define _TEXT_H_

/// Класс текста
class Text {
    public: 
    /// Массив символов
    char text[16];

    /// Базовый конструктор
    Text(char getText[16]) {
        strcpy(text, getText);
    }

    /// Установить текст: char*
    void SetText(char* getText) { strcpy(text, getText); }
    
    /// Установить текст: int
    void SetText(int getText) { 
        char array[16];
        itoa(getText, array, 10);
        strcpy(text, array);
    }

    /// Установить текст: float
    void SetText(float getText) { 
        char array[16];
        // dtostrf(getText, 6, 2, array);
        strcpy(text, array);
    }

    /// Получить число: int
    int GetInt() { return atoi(text); }
};

#endif

