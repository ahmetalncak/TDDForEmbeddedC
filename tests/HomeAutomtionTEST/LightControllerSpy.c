#include "LightControllerSpy.h"

static int lastId;
static int lastState;
static int lightStatesArr[MAX_LIGHTS];

void LightController_Create(void)
{
	lastId = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
	memset(lightStatesArr, LIGHT_STATE_UNKNOWN, sizeof(lightStatesArr));
}

void LightController_Destroy(void)
{
	lastId = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
	memset(lightStatesArr, LIGHT_STATE_UNKNOWN, sizeof(lightStatesArr));
}

void LightController_On(int id)
{
	lastId = id;
	lastState = LIGHT_ON;
	lightStatesArr[id] = LIGHT_ON;
}

void LightController_Off(int id)
{
	lastId = id;
	lastState = LIGHT_OFF;
	lightStatesArr[id] = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void)
{
	return lastId;
}

int LightControllerSpy_GetLastState(void)
{
	return lastState;
}

int LightControllerSpy_GetLightState(int id)
{
	return lightStatesArr[id];
}
