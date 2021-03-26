#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Object.h"
#include <assert.h>
#include "EventStep.h"

int main(void) {
	GM.startUp();
	LM.setLogToScreen();

	df::Object* obj1 = new df::Object(), * obj2 = new df::Object();
	int res;

	LM.writeLog("Registering with invalid manager\n");
	res = GM.registerInterest(obj1, "TEST_EVENT");
	assert(res == -1);

	LM.writeLog("Registering for same event\n");
	res = WM.registerInterest(obj1, "TEST_EVENT");
	assert(res == 0);
	res = WM.registerInterest(obj2, "TEST_EVENT");
	assert(res == 0);

	LM.writeLog("Unregistering from event\n");
	res = WM.unregisterInterest(obj1, "TEST_EVENT");
	assert(res == 0);
	res = WM.unregisterInterest(obj2, "TEST_EVENT");
	assert(res == 0);

	LM.writeLog("Registering for different events\n");
	res = WM.registerInterest(obj1, "TEST_EVENT");
	assert(res == 0);
	res = WM.registerInterest(obj2, "TEST_EVENT2");
	assert(res == 0);

	LM.writeLog("Unregistering from event\n");
	res = WM.unregisterInterest(obj1, "TEST_EVENT");
	assert(res == 0);
	res = WM.unregisterInterest(obj2, "TEST_EVENT2");
	assert(res == 0);

	LM.writeLog("Unregister again\n");
	res = WM.unregisterInterest(obj2, "TEST_EVENT2");
	assert(res == -1);

	LM.writeLog("Incorrect unregister\n");
	res = WM.registerInterest(obj1, "TEST_EVENT");
	assert(res == 0);
	res = WM.unregisterInterest(obj2, "TEST_EVENT");
	assert(res == -1);

	LM.writeLog("Registering step event interest\n");
	res = obj1->registerInterest(df::STEP_EVENT);
	assert(res == 0);
	LM.writeLog("Unregistering step event interest\n");
	res = obj1->unregisterInterest(df::STEP_EVENT);
	assert(res == 0);

	LM.writeLog("Registering custom event interest\n");
	res = obj1->registerInterest("CUSTOM EVENT");
	assert(res == 0);
	LM.writeLog("Unregistering custom event interest\n");
	res = obj1->unregisterInterest("CUSTOM EVENT");
	assert(res == 0);

	LM.writeLog("Registering custom event interest\n");
	res = obj1->registerInterest("CUSTOM EVENT");
	assert(res == 0);

	LM.writeLog("Registering step event interest\n");
	res = obj1->registerInterest(df::STEP_EVENT);
	assert(res == 0);

	LM.writeLog("Deleting obj1\n");
	delete obj1;

	LM.writeLog("Test Done.\n");

	GM.shutDown();
	return 0;
}