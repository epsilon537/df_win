#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "ObjectListIterator.h"
#include "Vector.h"
#include "Event.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "Clock.h"
#include <assert.h>
#include <stdlib.h>

class TestObject : public df::Object {
private:
	df::Color m_color;
	char m_c;
	int m_collision_count;

public:
	TestObject(df::Color color, char c);
	~TestObject();

	int draw();
	int eventHandler(const df::Event* p_e);
};

TestObject::TestObject(df::Color color, char c) : m_color(color), m_c(c), m_collision_count(0) {
	setType("Test Object");
}

TestObject::~TestObject() {
	printf("TestObject %d deleted.\n", getId());
}

int TestObject::draw() {
	DM.drawCh(getPosition(), m_c, m_color);
	return 0;
}

int TestObject::eventHandler(const df::Event* p_e) {
	assert(p_e);

	std::string eType = p_e->getType();

	if (eType == df::COLLISION_EVENT) {
		++m_collision_count;

		const df::EventCollision* ec = dynamic_cast<const df::EventCollision*>(p_e);
		df::Object* obj1 = ec->getObject1();
		df::Object* obj2 = ec->getObject2();
		df::Object* otherObj = (obj1 == this) ? obj2 : obj1;
		df::Vector v = ec->getPosition();

		LM.writeLog("Obj %d collision with obj %d at position (%f,%f)\n", getId(), otherObj->getId(), v.getX(), v.getY());

		m_color = df::RED;
		

		if (m_collision_count == 100) {
			WM.markForDelete(this);

			TestObject* obj3 = new TestObject(df::YELLOW, 'X');
			obj3->setSolidness(df::SPECTRAL);
			obj3->setPosition(df::Vector((float)DM.getHorizontal() * 0.25f, (float)DM.getVertical() * 0.25f));
			obj3->setVelocity(df::Vector(0.1f, 0));

			TestObject* obj4 = new TestObject(df::BLUE, '*');
			obj4->setSolidness(df::SPECTRAL);
			obj4->setPosition(df::Vector((float)DM.getHorizontal() * 0.75f, (float)DM.getVertical() * 0.25f));
			obj4->setVelocity(df::Vector(-0.1f, 0));
		}
	}
	else if (eType == df::OUT_EVENT) {
		LM.writeLog("Obj %d out of bounds\n", getId());
		setDirection(getDirection() * (-1.0f));
	}

	return 1;
}

int main(void) {
	GM.startUp();
	LM.setLogToScreen();

	TestObject *obj1 = new TestObject(df::YELLOW, 'X');
	obj1->setSolidness(df::HARD);
	obj1->setPosition(df::Vector((float)DM.getHorizontal() * 0.25f, (float)DM.getVertical() / 2));
	obj1->setVelocity(df::Vector(0.1f, 0));

	TestObject* obj2 = new TestObject(df::BLUE, '*');
	obj1->setSolidness(df::HARD);
	obj2->setPosition(df::Vector((float)DM.getHorizontal() * 0.75f, (float)DM.getVertical() / 2));
	obj2->setVelocity(df::Vector(-0.1f, 0));

	TestObject* obj3 = new TestObject(df::YELLOW, 'X');
	obj3->setSolidness(df::SOFT);
	obj3->setPosition(df::Vector((float)DM.getHorizontal() * 0.25f, (float)DM.getVertical() * 0.75f));
	obj3->setVelocity(df::Vector(0.1f, 0));

	TestObject* obj4 = new TestObject(df::BLUE, '*');
	obj4->setSolidness(df::SOFT);
	obj4->setPosition(df::Vector((float)DM.getHorizontal() * 0.75f, (float)DM.getVertical() * 0.75f));
	obj4->setVelocity(df::Vector(-0.1f, 0));

	printf("Starting Game Loop\n");

	GM.run();

	GM.shutDown();

	printf("Test completed.\n");
}