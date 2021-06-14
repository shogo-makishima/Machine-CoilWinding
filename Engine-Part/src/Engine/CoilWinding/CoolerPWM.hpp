#ifndef _COOLER_PWM_H_
#define _COOLER_PWM_H_

class CoolerPWM {
    private: 
    byte _value = 0;
    int _pin = 0;

    public:
    CoolerPWM(int pin) : _pin(pin) {};

    void SetValue(byte value) {
        _value = value;
    }

    byte GetValue() {
        return _value;
    }

    void Function(float x) {
        float y = map(pow(x, 1/4), 0, 1, 0, 255);
        SetValue(y);
    }
};

#endif