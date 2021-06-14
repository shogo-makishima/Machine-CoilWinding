#ifndef _PEDAL_H_
#define _PEDAL_H_

/// Пин педали
#define PEDAL_PIN A0

/// Минимальное значение нажатия
#define PEDAL_MIN 200
/// Максмиальное значение нажатия
#define PEDAL_MAX 620

/// Для сглаживания шипов графика нажатий
#define PEDAL_VALUES_COUNT 10

/// Пауза до следующего считывания
#define PEDAL_READ_PAUSE 25

/// Класс педали
class Pedal {
    private:
    /// Для сглаживания шипов графика нажатий
    short int _pedalValues[PEDAL_VALUES_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    /// Заполеность массива
    short int _counter = 0;

    public:
    /// Текущеее значение
    short int currentValue = 0;
    /// Обновить значения
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