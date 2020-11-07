#ifndef _VARIABLES_H_
#define _VARIABLES_H_

// #include "EEPROM.h"

static bool VDirection = true;

static int VCounter = 0;
void ChangeVCounter() {
    VCounter += (VDirection) ? 1 : -1;
}

static bool VMode = true;

#endif