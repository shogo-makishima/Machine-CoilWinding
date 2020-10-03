#ifndef _TEXT_H_
#define _TEXT_H_

class Text {
    public: 
    char text[16];

    Text(char getText[16]) {
        strcpy(text, getText);
    }

    void SetText(char* getText) { strcpy(text, getText); }

    void SetText(int getText) { 
        char array[16];
        itoa(getText, array, 10);
        strcpy(text, array);
    }

    void SetText(float getText) { 
        char array[16];
        // dtostrf(getText, 6, 2, array);
        strcpy(text, array);
    }

    int GetInt() { return atoi(text); }
};

#endif

