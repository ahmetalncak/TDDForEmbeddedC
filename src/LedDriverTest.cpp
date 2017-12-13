#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LedDriver.h"
}

TEST_GROUP(LedDriver)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(LedDriver, LedsOffAfterCreate)
{
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds);
	BYTES_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
	uint16_t virtualLeds;
	LedDriver_Create(&virtualLeds);
	LedDriver_TurnOn(1);
	BYTES_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
	uint16_t virtualLeds;
	LedDriver_Create(&virtualLeds);
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	CHECK_EQUAL(0, virtualLeds);
}