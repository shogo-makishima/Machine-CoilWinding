#ifndef _VARIABLES_H_
#define _VARIABLES_H_

static int Counter = 0;
void ChangeCounter(bool direction) {
    Counter += (direction) ? 1 : -1;
}


#endif