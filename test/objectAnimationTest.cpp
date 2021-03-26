#include "GameManager.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "Sprite.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "Object.h"
#include "EventOut.h"
#include "EventStep.h"
#include <assert.h>

class TestObject : public df::Object {
private:
	
	
public:
	TestObject();
	~TestObject();

	// Returns 0 if OK, -1 on error.
	int draw() {
		if (getAnimation().getSprite()->getLabel() == "Saucer") {
			LM.writeLog("%d Saucer drawn\n", GM.getFrameCount());
		}

		return Object::draw();
	}

	int eventHandler(const df::Event* p_e);
};

TestObject::TestObject() {
	setType("Test Object");

	registerInterest(df::STEP_EVENT);
	registerInterest(df::OUT_EVENT);
}

int TestObject::eventHandler(const df::Event* p_e) {
	assert(p_e);

	std::string eType = p_e->getType();

	if (eType == df::OUT_EVENT) {
		setVelocity(getVelocity()*(-1.0));

		return 1;
	}
	else if (eType == df::STEP_EVENT) {
		const df::EventStep* es = dynamic_cast<const df::EventStep*>(p_e);

		if (es->getStepCount() == 100) {
			df::Box viewBox = WM.getView();
			viewBox.setCorner(df::Vector(3, -3));
			WM.setView(viewBox);
		}

		if (es->getStepCount() == 250) {
			df::Sprite* spr = getAnimation().getSprite();
			assert(spr);
			spr->setSlowdown(spr->getSlowdown()*2);
		}

		if (es->getStepCount() == 500)
			getAnimation().setSlowdownCount(-1);
	}

	return 0;
}

TestObject::~TestObject() {
}


int main(void) {
	GM.startUp();
	LM.setLogToScreen();

	int res = RM.loadSprite("sprites/orig.txt", "Saucer");
	assert(res == 0);

	res = RM.loadSprite("sprites/ship-spr.txt", "Ship");
	assert(res == 0);

	TestObject ship;
	df::Box shipBox = ship.getBox();
	
	assert(shipBox.getCorner() == df::Vector(0, 0));
	assert(shipBox.getHorizontal() == 1);
	assert(shipBox.getVertical() == 1);

	ship.setSprite("Ship");
	shipBox = ship.getBox();
	assert(shipBox.getCorner() == df::Vector(-2.0f, -1.5f));
	assert(shipBox.getHorizontal() == 4);
	assert(shipBox.getVertical() == 3);

	ship.setPosition(df::Vector((float)DM.getHorizontal() * 0.75f, (float)DM.getVertical() / 2));
	ship.setVelocity(df::Vector(0.1f, 0.05f));

	TestObject saucer;
	saucer.setSprite("Saucer");
	df::Box saucerBox = saucer.getBox();

	assert(saucerBox.getCorner() == df::Vector(-3.0f, -1.0f));
	assert(saucerBox.getHorizontal() == 6);
	assert(saucerBox.getVertical() == 2);

	saucer.setPosition(df::Vector((float)DM.getHorizontal() *0.35f, (float)DM.getVertical() / 2));
	saucer.setVelocity(df::Vector(-0.05f, -0.1f));

	GM.run();

	res = RM.unloadSprite("Saucer");
	assert(res == 0);

	res = RM.unloadSprite("Ship");
	assert(res == 0);

	LM.writeLog("Test Complete.");

	GM.shutDown();
}
