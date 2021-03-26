#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "ObjectListIterator.h"
#include "Vector.h"
#include "Event.h"
#include "EventMouse.h"
#include "Clock.h"
#include <assert.h>
#include <stdlib.h>

static int objFrameCount = 0;

class TestObject : public df::Object {
private:
	df::Color m_color;

public:
	TestObject(df::Color color);
	~TestObject();

	int eventHandler(const df::Event* p_e);
	int draw();
};

TestObject* objs[3];
TestObject* moreObjs[3];

TestObject::TestObject(df::Color color) : m_color(color) {
	setType("Test Object");
}

TestObject::~TestObject() {
	printf("TestObject %d deleted.\n", getId());
}

int TestObject::eventHandler(const df::Event* p_e) {
	assert(p_e);
	LM.writeLog("obj. %d, eventHandler received event: %s\n", getId(), p_e->getType().c_str());

	if (getId() == 1) {
		std::string eType = p_e->getType();

		if (eType == df::MSE_EVENT) {
			const df::EventMouse* em = dynamic_cast<const df::EventMouse*>(p_e);

			if (em->getMouseAction() == df::CLICKED) {
				GM.setGameOver();
			}
			else if (em->getMouseAction() == df::MOVED) {

				df::Vector v = em->getMousePosition();
				v.scale(0.1f);
				setPosition(v);
			}
		}

		return 1;
	}

	setPosition(df::Vector((float)(abs(rand()) % DM.getHorizontal()), (float)(abs(rand()) % DM.getVertical())));

	if (objFrameCount > 500) {
		for (int ii = 0; ii < 3; ii++) {
			moreObjs[ii]->setPosition(objs[ii]->getPosition());
		}
	}

	if (objFrameCount > 1000) {
		for (int ii = 0; ii < 3; ii++) {
			moreObjs[ii]->setAltitude(3);
		}
	}

#if 0
	if ((objFrameCount > 1500) && (this != objs[0]))
		WM.markForDelete(this);
#endif 

	return 1;
}

int TestObject::draw() {
	if (getId()==1)
		DM.drawCh(getPosition(), 'X', m_color);
	else
		DM.drawCh(getPosition(), '*', m_color);

	return 0;
}

int main(void) {
	GM.startUp();
	assert(GM.isStarted());
	assert(LM.isStarted());

	int ii;

	for (ii = 0; ii < 3; ii++) {
		objs[ii] = new TestObject(df::YELLOW);
	}

	for (ii = 0; ii < 3; ii++) {
		moreObjs[ii] = new TestObject(df::BLUE);
		moreObjs[ii]->setAltitude(1);
	}

	LM.writeLog("Starting game loop.\n");
	df::Clock clock;

	GM.run();

	LM.writeLog("Game loop ended. duration: %d us.\n", clock.split_us());
	LM.writeLog("Frame counter: %d\n", GM.getFrameCount());
	LM.writeLog("Frame time: %d ms\n", GM.getFrameTimeMs());
	GM.shutDown();
	assert(!GM.isStarted());
	assert(!LM.isStarted());
	printf("Game Manager Test completed.\n");
	return 0;
}