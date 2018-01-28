#include "LedDriver.h"
#include "RuntimeError.h"

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};
enum {FIRST_LED = 1, LAST_LED = 16};

static uint16_t *ledsAddress;
static uint16_t ledsImage;

static uint16_t convertLedNumberToBit(int ledNumber)
{
	return 1 << (--ledNumber);
}

static BOOL isLedOutOfBounds(int ledNumber)
{
	if ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED))
	{
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
		return TRUE;
	}

	return FALSE;
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

void LedDriver_Create(uint16_t* address)
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

BOOL LedDriver_IsOn(int ledNumber)
{
	if (isLedOutOfBounds(ledNumber))
	{
		return FALSE; // always behave like it is off when out off bounds
	}

	if ((ledsImage & convertLedNumberToBit(ledNumber)) == 0)
	{
		return FALSE; // FALSE
	}

	return TRUE; // TRUE: means Led is on
}

BOOL LedDriver_IsOff(int ledNumber)
{
	if (LedDriver_IsOn(ledNumber) == 0)
	{
		return TRUE;
	}
	return FALSE;
}
