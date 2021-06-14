#ifndef _PEDAL_H_
#define _PEDAL_H_

#define PEDAL_PIN A0

#define PEDAL_MIN 200
#define PEDAL_MAX 620

#define PEDAL_VALUES_COUNT 10

#define PEDAL_READ_PAUSE 25

class Pedal {
    private:
    short int _pedalValues[PEDAL_VALUES_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    short int _counter = 0;

    public:
    short int currentValue = 0;
    void Update() {
        int currentRead = analogRead(PEDAL_PIN);
	
        if (currentRead >= 900) currentRead = 0;
        else currentRead = Math::Clamp(PEDAL_MIN, PEDAL_MAX, currentRead) - PEDAL_MIN;

        _pedalValues[_counter] = currentRead;
        _counter++;

        if (_counter >= PEDAL_VALUES_COUNT) {
            short int sum = 0;
            for (int i = 0; i < PEDAL_VALUES_COUNT; i++) sum += _pedalValues[i];
            currentValue = sum / PEDAL_VALUES_COUNT;
            _counter = 0;
        }
    }
};

#endif