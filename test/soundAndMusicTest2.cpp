#include "ResourceManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include <assert.h>
#include <stdio.h>
#include <Windows.h>

int main(void) {
	int res;

	GM.startUp();
	LM.setLogToScreen();

	res = RM.loadSound("sounds\\fire.wav", "fire");
	assert(res == 0);
	assert(RM.getSound("fire"));
	res = RM.unloadSound("fire");
	assert(res == 0);
	res = RM.unloadSound("fire");
	assert(res == -1);
	res = RM.loadSound("sounds\\wrong.wav", "wrong");
	assert(res == -1);
	assert(RM.getSound("wrong") == 0);

	res = RM.loadMusic("sounds\\start-music.wav", "start-music");
	assert(res == 0);
	assert(RM.getMusic("start-music"));
	res = RM.unloadMusic("start-music");
	assert(res == 0);
	res = RM.unloadMusic("start-music");
	assert(res == -1);
	res = RM.loadMusic("sounds\\wrong.wav", "wrong");
	assert(res == -1);
	assert(RM.getMusic("wrong") == 0);

	GM.shutDown();

	printf("Test Complete.\n");
	return 0;
}