#include "Engine/Engine.h"

#include "Engine/Timer.h"

void SendData();

Timer sendDataTimer = Timer(500, [] {
	SendData();
});

void setup() {
	Serial.begin(115200);
	Serial.println("DEBUG CONSOLE");

	CustomSerial::customSerial.begin(76800);

	Data::Load();

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

	sendDataTimer.Update();
}

void SendData() {
	if (!Data::b_isInit) return;

	if (Math::Round(Data::dataContainer.countTurn, 1) != Math::Round(CoilWinding::last_countTurn, 1)) {
        CustomSerial::customSerial.print("D20 ");
		// Math::Round(Data::dataContainer.countTurn, 1) CoilWinding::pedal.currentValue, 1
        CustomSerial::customSerial.println(Math::Round(Data::dataContainer.countTurn, 1));

		sendDataTimer.Reset();
    }

	CoilWinding::last_countTurn = Data::dataContainer.countTurn;
}