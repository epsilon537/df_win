#include "LogManager.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
	int res;
	bool res_bool;

	res = LM.writeLog("writeLog before start.\n");
	assert(res < 0);

	res = LM.startUp();
	assert(res == 0);

	res_bool = LM.isStarted();
	assert(res_bool == true);

	res = LM.startUp();
	assert(res == 0);

	res = LM.writeLog("writeLog without arguments.\n");
	assert(res > 0);

	res = LM.writeLog("writeLog with arguments: %s, %d, %f\n", "test", 42, 3.14);
	assert(res > 0);

	LM.setLogTime(true);

	res = LM.writeLog("writeLog with timestamp.\n");
	assert(res > 0);

	res = LM.writeLog("writeLog with arguments with timestamp: %s, %d, %f\n", "test", 42, 3.14);
	assert(res > 0);

	LM.setFlush();
	res = LM.writeLog("Enabled flush.\n");
	assert(res > 0);

	res = LM.writeLog(df::DBG_LVL, "Debug Level writeLog.\n");
	assert(res == 0);

	res = LM.writeLog(df::INFO_LVL, "Info Level writeLog.\n");
	assert(res > 0);

	res = LM.writeLog(df::INFO_LVL, "Important Level writeLog.\n");
	assert(res > 0);

	LM.setLogLevel(df::DBG_LVL - 1);
	res = LM.writeLog("Set log level below debug.\n");
	assert(res > 0);

	res = LM.writeLog(df::DBG_LVL, "Debug Level writeLog.\n");
	assert(res > 0);

	res = LM.writeLog(df::INFO_LVL, "Info Level writeLog.\n");
	assert(res > 0);

	res = LM.writeLog(df::IMPORTANT_LVL, "Important Level writeLog.\n");
	assert(res > 0);

	LM.setLogLevel(df::INFO_LVL + 1);
	res = LM.writeLog("Set log level above info.\n");
	assert(res > 0);

	res = LM.writeLog(df::DBG_LVL, "Debug Level writeLog.\n");
	assert(res == 0);

	res = LM.writeLog(df::INFO_LVL, "Info Level writeLog.\n");
	assert(res == 0);

	res = LM.writeLog(df::IMPORTANT_LVL, "Important Level writeLog.\n");
	assert(res > 0);

	res = LM.writeLog("Shutting down.\n");
	assert(res > 0);

	LM.shutDown();
	res_bool = LM.isStarted();
	assert(res_bool == false);

	res = LM.writeLog("writeLog after shutdown.\n");
	assert(res < 0);

	printf("LogManagerTest completed successfully.\n");

	return 0;
}