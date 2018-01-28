#ifndef _FAKE_TIME_SERVICE_H_
#define _FAKE_TIME_SERVICE_H_

#include "TimeService.h"

void FakeTimeService_SetMinute(int min);
void FakeTimeService_SetDay(int day);
WakeUpCallback FakeTimeService_GetAlarmCallback(void);
int FakeTimeService_GetAlarmPeriod(void);
#endif