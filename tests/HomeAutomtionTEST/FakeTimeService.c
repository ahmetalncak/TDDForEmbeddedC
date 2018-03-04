#include "FakeTimeService.h"
#include "common.h"

static Time fakeTime;
static WakeUpCallback callback;
static int period;

void TimeService_GetTime(Time* time)
{
	*time = fakeTime;
}

void FakeTimeService_SetMinute(int min)
{
	fakeTime.minuteOfDay = min;
}

void FakeTimeService_SetDay(int day)
{
	fakeTime.dayOfWeek = day;
}

WakeUpCallback FakeTimeService_GetAlarmCallback(void)
{
	return callback;
}
int FakeTimeService_GetAlarmPeriod(void)
{
	return period;
}

void TimeService_SetPeriodicAlarmInSeconds(int secs, WakeUpCallback cb)
{
	callback = cb;
	period = secs;
}

void TimeService_CancelPeriodicAlarmInSeconds(int secs, WakeUpCallback cb)
{
	if ((cb == callback) && (period == secs))
	{
		callback = NULL;
		period = 0;
	}
}
