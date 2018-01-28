#ifndef _TIME_SERVICE_H_
#define _TIME_SERVICE_H_

typedef struct _Time
{
	int minuteOfDay;
	int dayOfWeek;
} Time;

enum { TIME_UNKNOWN = -1 };
typedef void (*WakeUpCallback) (void);

void TimeService_GetTime(Time* time);
void TimeService_SetPeriodicAlarmInSeconds(int secs, WakeUpCallback cb);
void TimeService_CancelPeriodicAlarmInSeconds(int secs, WakeUpCallback cb);
#endif
