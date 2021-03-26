#include "GameManager.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "Sprite.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include <assert.h>

int main(void) {
	GM.startUp();
	LM.setLogToScreen();

	df::Animation ship;
	df::Animation saucer;

	int res = RM.loadSprite("sprites/orig.txt", "Saucer");
	assert(res == 0);

	res = RM.loadSprite("sprites/ship-spr.txt", "Ship");
	assert(res == 0);

	ship.setSprite(RM.getSprite("Ship"));
	saucer.setSprite(RM.getSprite("Saucer"));

	assert(ship.getSprite() == RM.getSprite("Ship"));
	assert(saucer.getSprite() == RM.getSprite("Saucer"));

	ship.setIndex(1);
	saucer.setIndex(2);

	assert(ship.getIndex() == 1);
	assert(saucer.getIndex() == 2);

	saucer.setSlowdownCount(-1);
	assert(saucer.getSlowdownCount() == -1);

	res = ship.draw(df::Vector((float)DM.getHorizontal()/2, (float)DM.getVertical()/2));
	assert(res == 0);

	assert(ship.getSlowdownCount() == 1);
	assert(ship.getIndex() == 1);
	
	res = ship.draw(df::Vector((float)DM.getHorizontal() / 2, (float)DM.getVertical() / 2));
	assert(res == 0);
	assert(ship.getSlowdownCount() == 2);
	assert(ship.getIndex() == 1);

	res = ship.draw(df::Vector((float)DM.getHorizontal() / 2, (float)DM.getVertical() / 2));
	assert(res == 0);
	assert(ship.getSlowdownCount() == 0);
	assert(ship.getIndex() == 0);

	res = saucer.draw(df::Vector((float)DM.getHorizontal() / 2, (float)DM.getVertical() / 2));
	assert(res == 0);
	assert(saucer.getSlowdownCount() == -1);
	assert(saucer.getIndex() == 2);

	res = RM.unloadSprite("Saucer");
	assert(res == 0);

	res = RM.unloadSprite("Ship");
	assert(res == 0);

	LM.writeLog("Test Complete.");

	GM.shutDown();
}