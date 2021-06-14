#ifndef _TIMER_H_
#define _TIMER_H_

/// Callback для таймера
typedef void(*callbackTimerZero)();

/// Класс таймера
class Timer{
	public:
	/// Время до срабатывания
	float time = 0.0;
	/// Callback для таймера
	std::function<void()> Callback;

	/// Базовый конструктор
	Timer(float seconds, std::function<void()> callback = []{Serial.println("Timer is ZERO!");}) {
		time = seconds;
		m_timing = millis();
		m_time = time;

		Callback = callback;
	}

	/// Функция обновления
	void Update() {
		if (time > 0) { 
			time -= millis() - m_timing;
			m_timing = millis();
		}
		
		if (time <= 0) {
			Callback();
			Reset();
		}
	}

	/// Обнулить таймер
	void Reset() {
		time = m_time;
		m_timing = millis();
	}

	private:
	/// Дополнительное хранение времени
	float m_time = 0;
	/// Дополнительное хранение времени
	unsigned long m_timing;
};

#endif