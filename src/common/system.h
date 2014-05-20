#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "defines.h"

#define STATE_DISCONNECTED	0x01
#define STATE_IDLE			0x02
#define STATE_OUTPUTACTIVE	0x03

static int currentState;

void initSystem(void);

#endif