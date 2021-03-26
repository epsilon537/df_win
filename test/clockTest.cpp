#include "Clock.h"
#include "LogManager.h"
#include <Windows.h>
#include <assert.h>

int main(void) {
	int res;

	res = LM.startUp();
	assert(res == 0);

	timeBeginPeriod(1);

	LM.writeLog("Creating clock.\n");
	df::Clock clock;

	Sleep(20);
	long int clock_res = clock.delta_us();
	LM.writeLog("Clock delta after sleep(20):%d\n", clock_res);
	Sleep(20); //This is in ms.
	clock_res = clock.delta_us();
	LM.writeLog("Clock delta after sleep(20):%d\n", clock_res);
	Sleep(20);
	clock_res = clock.split_us();
	LM.writeLog("Clock split after sleep(20):%d\n", clock_res);
	Sleep(20);
	clock_res = clock.split_us();
	LM.writeLog("Clock split after sleep(20):%d\n", clock_res);

	LM.shutDown();

	timeEndPeriod(1);

	printf("Clock Test completed successfully.\n");

	return 0;
}
