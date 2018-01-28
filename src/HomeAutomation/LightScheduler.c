#include "LightScheduler.h"
#include "LightController.h"
#include "common.h"

enum { UNUSED = -1, TURN_OFF = 0, TURN_ON = 1, MAX_EVENTS = 128 };

typedef struct
{
	int id;
	Day day;
	int minuteOfDay;
	int event;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

static BOOL isIdInRange(int id)
{
	return ((id >= 0) && (id < MAX_LIGHTS));
}
static int scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
	int i = 0;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		if (scheduledEvents[i].id == UNUSED)
		{
			scheduledEvents[i].day = day;
			scheduledEvents[i].minuteOfDay = minuteOfDay;
			scheduledEvents[i].event = event;
			scheduledEvents[i].id = id;
			return LS_OK;
		}
	}

	return LS_TOO_MANY_EVENTS;
}

static void operateLight(ScheduledLightEvent* lightEvent)
{
	if (lightEvent->event == TURN_ON)
	{
		LightController_On(lightEvent->id);
	}
	else if (lightEvent->event == TURN_OFF)
	{
		LightController_Off(lightEvent->id);
	}
}

static BOOL doesLightRespondToday(Time* time, Day reactionday)
{
	Day today = time->dayOfWeek;

	if (reactionday == EVERYDAY)
		return TRUE;
	if (reactionday == today)
		return TRUE;
	if ((reactionday == WEEKEND) &&
		((today == SATURDAY) || (today == SUNDAY)))
		return TRUE;
	if ((reactionday == WEEKDAY) &&
		(today >= MONDAY) && (today <= FRIDAY))
		return TRUE;

	return FALSE;
}

static void processEventDueNow(Time* time, ScheduledLightEvent* lightEvent)
{
	int reactionDay = lightEvent->day;

	if (lightEvent->id == UNUSED)
		return;
	if (!doesLightRespondToday(time, reactionDay))
		return;
	if (time->minuteOfDay != lightEvent->minuteOfDay)
		return;

	operateLight(lightEvent);
}
void LightScheduler_Create(void)
{
	int i = 0;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		scheduledEvents[i].id = UNUSED;
	}
	TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_Destroy(void)
{
	TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_WakeUp(void)
{
	int i = 0;
	Time time;

	TimeService_GetTime(&time);
	
	for (i = 0; i < MAX_EVENTS; i++)
	{
		processEventDueNow(&time, &scheduledEvents[i]);
	}
}

int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
	if (!isIdInRange(id))
		return LS_OUT_OF_BOUNDS;
	return scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
	if (!isIdInRange(id))
		return LS_OUT_OF_BOUNDS;
	return scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay)
{
	int i;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		if ((scheduledEvents[i].id == id) &&
			(scheduledEvents[i].day == day) &&
			(scheduledEvents[i].minuteOfDay == minuteOfDay))
		{
			scheduledEvents[i].id = UNUSED;
		}
	}
}
