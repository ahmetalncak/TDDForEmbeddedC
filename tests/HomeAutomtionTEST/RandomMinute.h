#ifndef _RANDOM_MINUTE_H_
#define _RANDOM_MINUTE_H_

void RandomMinute_Create(int bound);
int RandomMinute_Get(void);

void FakeRandomMinute_SetFirstAndIncrement(int first, int inc);
#endif // _RANDOM_MINUTE_H_
