#include "RandomMinute.h"
#include "time.h"

static int gBound;

void RandomMinute_Create(int bound)
{
	gBound = bound;
}

int RandomMinute_Get(void)
{
	return gBound - (rand() % (2 * gBound + 1));
}

void FakeRandomMinute_SetFirstAndIncrement(int first, int inc)
{

}

