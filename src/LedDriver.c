#include "LedDriver.h"

static unsigned short *ledsAddress;

void LedDriver_Create(unsigned short* address)
{
	ledsAddress = address;
	*ledsAddress = 0;
}

void LedDriver_Destroy(void)
{

}

void LedDriver_TurnOn(int ledNumber)
{
	*ledsAddress = 1;
}

void LedDriver_TurnOff(int ledNumber)
{
	*ledsAddress = 0;
}