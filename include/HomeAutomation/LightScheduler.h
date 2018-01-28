#ifndef _LIGHT_SCHEDULER_H_
#define _LIGHT_SCHEDULER_H_

#include "TimeService.h"

typedef enum {
	NONE = -1, EVERYDAY = 10, WEEKDAY, WEEKEND,
	SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
} Day;

enum {
	LS_OK = 1, LS_TOO_MANY_EVENTS, LS_OUT_OF_BOUNDS
};
void LightScheduler_Create(void);
void LightScheduler_Destroy(void);

int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_WakeUp(void);
void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay);
#endif
