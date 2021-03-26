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

class TestObject : public df::Object {
private:
	df::Color m_color;
	char m_c;

public:
	TestObject(df::Color color, char c);
	~TestObject();

	int draw();
};

TestObject::TestObject(df::Color color, char c) : m_color(color), m_c(c) {
	setType("Test Object");
}

TestObject::~TestObject() {
	printf("TestObject %d deleted.\n", getId());
}

int TestObject::draw() {
		DM.drawCh(getPosition(), m_c, m_color);
	return 0;
}

int main(void) {
	GM.startUp();

	TestObject obj1(df::YELLOW, 'X');
	obj1.setPosition(df::Vector((float)DM.getHorizontal()/2, (float)DM.getVertical()/2));
	obj1.setVelocity(df::Vector(0.1f, 0.1f));

	TestObject obj2(df::BLUE, '*');
	obj2.setPosition(df::Vector((float)DM.getHorizontal()/2, (float)DM.getVertical()/2));
	obj2.setVelocity(df::Vector(-0.1f, -0.1f));

	TestObject obj3(df::WHITE, 'O');
	obj3.setPosition(df::Vector((float)DM.getHorizontal()/2, (float)DM.getVertical()/2));
	obj3.setVelocity(df::Vector(0.1f, -0.1f));

	TestObject obj4(df::GREEN, '/');
	obj4.setPosition(df::Vector((float)DM.getHorizontal()/2, (float)DM.getVertical()/2));
	obj4.setVelocity(df::Vector(-0.1f, 0.1f));

	printf("Starting Game Loop\n");

	GM.run();

	GM.shutDown();

	printf("Test completed.\n");
}