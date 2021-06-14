#include "Engine/Engine.h"

void setup() {
	Serial.begin(115200);
	Serial.println("DEBUG CONSOLE");

	CustomSerial::customSerial.begin(76800);

	CoilWinding::Init();
}

void loop() {
	CoilWinding::Update();

	CustomSerial::ReadByte();
	if (CustomSerial::b_bufferIsFull) {
		CustomSerial::PrintBuffer();
		CustomSerial::ParseBuffer();
		CustomSerial::ClearBuffer();
		CustomSerial::b_bufferIsFull = false;
	}

	if (CoilWinding::countAxis != CoilWinding::last_countAxis) {
        CustomSerial::customSerial.print("D20 ");
        CustomSerial::customSerial.println(CoilWinding::countAxis);
    }

	CoilWinding::last_countAxis = CoilWinding::countAxis;
}