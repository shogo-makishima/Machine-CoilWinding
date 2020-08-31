#ifndef _TEXT_H_
#define _TEXT_H_

class Text {
    public: 
    char* text;

    Text(char* getText) : text(getText) {}

    void SetText(char* getText) { text = getText; }

    void SetText(int getText) { 
        char array[32];
        itoa(getText, array, 10);

        text = array;
    }

    void SetText(float getText) { 
        char array[32];
        dtostrf(getText, 6, 2, array);

        text = array;
    }

    int GetInt() { return atoi(text); }
};

#endif

