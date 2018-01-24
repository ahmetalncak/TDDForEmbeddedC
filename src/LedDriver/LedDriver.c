#include "LedDriver.h"
#include "RuntimeError.h"

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};
enum {FIRST_LED = 1, LAST_LED = 16};

static unsigned short *ledsAddress;
static unsigned short ledsImage;

static unsigned short convertLedNumberToBit(int ledNumber)
{
	return 1 << (--ledNumber);
}

static unsigned char isLedOutOfBounds(int ledNumber)
{
	return ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED));
}

static void setLedImageBit(int ledNumber)
{
	ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber)
{
	ledsImage &= ~(convertLedNumberToBit(ledNumber));
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
	if (isLedOutOfBounds(ledNumber))
	{
		return;
	}
	setLedImageBit(ledNumber);
	updateHW();
}

void LedDriver_TurnOff(int ledNumber)
{
	if (isLedOutOfBounds(ledNumber))
	{
		return;
	}

	clearLedImageBit(ledNumber);
	updateHW();
}

void LedDriver_TurnAllOn(void)
{
	ledsImage = ALL_LEDS_ON;
	updateHW();
}

void LedDriver_TurnAllOff(void)
{
	ledsImage = ALL_LEDS_OFF;
	updateHW();
}

unsigned char LedDriver_IsOn(int ledNumber)
{
	if (isLedOutOfBounds(ledNumber))
	{
		return 0; // always behave like it is off when out off bounds
	}

	if ((ledsImage & convertLedNumberToBit(ledNumber)) == 0)
	{
		return 0; // FALSE
	}

	return 1; // TRUE: means Led is on
}

unsigned char LedDriver_IsOff(int ledNumber)
{
	if (LedDriver_IsOn(ledNumber) == 0)
	{
		return 1;
	}
	return 0;
}
