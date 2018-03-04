#include "CppUTest/TestHarness.h"

extern "C"
{
#include "FakeTimeService.h"
}

TEST_GROUP(FakeTimeService)
{
	void setup()
	{
	}

	void teardown()
	{
	}
};

IGNORE_TEST(FakeTimeService, Create)
{
	Time time;
	TimeService_GetTime(&time);
	LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
	LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set)
{
	Time time;
	FakeTimeService_SetMinute(42);
	FakeTimeService_SetDay(3);
	TimeService_GetTime(&time);
	LONGS_EQUAL(42, time.minuteOfDay);
	LONGS_EQUAL(3, time.dayOfWeek);
}
