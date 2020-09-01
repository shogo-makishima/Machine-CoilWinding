#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "EEPROM.h"

static bool VDirection = true;

static int VCounter = 0;
void ChangeVCounter() {
    VCounter += (VDirection) ? 1 : -1;
}

static bool VMode = true;

static bool VFirstLoad = true;
static long int VSpeedINT = 0; // size = 4 byte

static int VSpeed[6] = { 0, 0, 0, 0, 0, 0, };
int EEMEM VSpeed_ADDR[6];

void EnterVSpeedInt() {
    Serial.println("[VSPEED] { " + String(VSpeed[0]) + ", " + String(VSpeed[1]) + ", ... }");
    VSpeedINT = VSpeed[0] * 100000 + VSpeed[1] * 10000 + VSpeed[2] * 1000 + VSpeed[3] * 100 + VSpeed[4] * 10 + VSpeed[5] * 1; 
    Serial.println("[SPEED] " + String(VSpeedINT));
}

void ClearVSpeed() {
    for (int i = 0; i < 6; i++) VSpeed[i] = 0;
}

void LoadVSpeedInt() {
    Serial.println("[LOAD] VSpeed");
    eeprom_read_block((void*)&VSpeed, (const void*)&VSpeed_ADDR, sizeof(VSpeed));
    EnterVSpeedInt();
}

void SaveVSpeedInt() {
    Serial.println("[SAVE] VSpeed");
    eeprom_write_block((void*)&VSpeed, (const void*)&VSpeed_ADDR, sizeof(VSpeed));
}

#endif