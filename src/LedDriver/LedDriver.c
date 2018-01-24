#include "LedDriver.h"

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};

static unsigned short *ledsAddress;
static unsigned short ledsImage;

static unsigned short convertLedNumberToBit(int ledNumber)
{
	return 1 << (--ledNumber);
}

static void updateHW(void)
{
	*ledsAddress = ledsImage;
}

void LedDriver_Create(unsigned short* address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	updateHW();
}

void LedDriver_Destroy(void)
{

}

void LedDriver_TurnOn(int ledNumber)
{
	if ((ledNumber <= 0) || (ledNumber > 16))
	{
		return;
	}

	ledsImage |= convertLedNumberToBit(ledNumber);
	updateHW();
}

void LedDriver_TurnOff(int ledNumber)
{
	if ((ledNumber <= 0) || (ledNumber > 16))
	{
		return;
	}

	ledsImage &= ~(convertLedNumberToBit(ledNumber));
	updateHW();
}

void LedDriver_TurnAllOn(void)
{
	ledsImage = ALL_LEDS_ON;
	updateHW();
}
