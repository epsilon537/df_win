#include "ResourceManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "Sprite.h"
#include "Frame.h"

#include <assert.h>

int main(void) {
	GM.startUp();
	LM.setLogToScreen();

	int res = RM.loadSprite("sprites/orig.txt", "Saucer");
	assert(res == 0);
	
	res = RM.loadSprite("sprites/ship-spr.txt", "Ship");
	assert(res == 0);

	res = RM.loadSprite("sprites/orig.txt", "Saucer");
	assert(res == -1);

	df::Sprite* sprite = RM.getSprite("Wrong");
	assert(!sprite);

	sprite = RM.getSprite("Ship");
	assert(sprite);
	df::Frame frame = sprite->getFrame(1);
	assert(!frame.isEmpty());

	sprite = RM.getSprite("Saucer");
	assert(sprite);

	assert(sprite->getWidth() == 6);
	assert(sprite->getHeight() == 2);
	assert(sprite->getColor() == df::GREEN);
	assert(sprite->getLabel() == "Saucer");
	assert(sprite->getSlowdown() == 4);
	assert(sprite->getFrameCount() == 5);

	frame = sprite->getFrame(0);
	assert(!frame.isEmpty());
	assert(frame.getHeight() == 2);
	assert(frame.getWidth() == 6);
	assert(frame.getString() == " ____ /____\\");

	frame = sprite->getFrame(4);
	assert(!frame.isEmpty());
	assert(frame.getHeight() == 2);
	assert(frame.getWidth() == 6);
	assert(frame.getString() == " ____ /o___\\");

	res = RM.unloadSprite("Saucer");
	assert(res == 0);

	res = RM.unloadSprite("Saucer");
	assert(res == -1);

	res = RM.loadSprite("sprites/beginDelMissing.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/endDelMissing.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/colorMissing.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/framesMissing.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/incorrectWidth.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/missingEndFrame.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/bodyMissing.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/footerMissing.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/heightMissing.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/widthMissing.txt", "Saucer");
	assert(res == -1);
	res = RM.loadSprite("sprites/slowdownMissing.txt", "Saucer");
	assert(res == -1);
	LM.writeLog("Test Complete.\n");
	GM.shutDown();
	return 0;
}