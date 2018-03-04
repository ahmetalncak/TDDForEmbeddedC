#ifndef _LIGHT_CONTROLLER_SPY_H
#define _LIGHT_CONTROLLER_SPY_H

#include "LightController.h"

enum 
{
	LIGHT_ID_UNKNOWN = -1, LIGHT_STATE_UNKNOWN = -1,
	LIGHT_OFF = 0, LIGHT_ON = 1
};

int LightControllerSpy_GetLightState(int id);
int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);
#endif
