#ifndef _TIMER_H_
#define _TIMER_H_

typedef void(*callbackTimerZero)();

class Timer{
	public:
	float time = 0.0;
	callbackTimerZero Callback;


	Timer(float seconds, callbackTimerZero callback = []{Serial.println("Timer is ZERO!");}) {
		time = seconds;
		m_timing = millis();
		m_time = time;

		Callback = callback;
	}

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

	void Reset() {
		time = m_time;
		m_timing = millis();
	}

	private:
	float m_time = 0;
	unsigned long m_timing;
};

#endif