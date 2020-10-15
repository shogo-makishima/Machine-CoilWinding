#ifndef _CUSTOM_STEPPER_H_
#define _CUSTOM_STEPPER_H_

class Stepper {
    public:
    int IN1, IN2, IN3, IN4;

    Stepper(int _IN1, int _IN2, int _IN3, int _IN4) {
        IN1 = _IN1; IN2 = _IN2; IN3 = _IN3; IN4 = _IN4;
    }

    void INIT() {
        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(IN4, OUTPUT);
    }

    void Move() {
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, HIGH); 
        digitalWrite(IN3, LOW); 
        digitalWrite(IN4, HIGH);
    }
};

/*

void loop() {
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW); 
    digitalWrite(in3, LOW); 
    digitalWrite(in4, HIGH);
    delay(dl);

    digitalWrite(in1, HIGH); 
    digitalWrite(in2, HIGH); 
    digitalWrite(in3, LOW); 
    digitalWrite(in4, LOW);
    delay(dl);

    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH); 
    digitalWrite(in3, HIGH); 
    digitalWrite(in4, LOW);
    delay(dl);

    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW); 
    digitalWrite(in3, HIGH); 
    digitalWrite(in4, HIGH);
    delay(dl);
}
*/

#endif