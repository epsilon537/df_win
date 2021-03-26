#include "EventCollision.h"
#include "Object.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
	df::EventCollision ev;
	assert(ev.getType() == df::COLLISION_EVENT);

	assert(ev.getObject1() == 0);
	assert(ev.getObject2() == 0);
	assert(ev.getPosition() == df::Vector(0,0));

	df::Object obj1, obj2;

	df::EventCollision ev2(&obj1, &obj2, df::Vector(2, 3));
	assert(ev.getType() == df::COLLISION_EVENT);
	assert(ev2.getObject1() == &obj1);
	assert(ev2.getObject2() == &obj2);
	assert(ev2.getPosition() == df::Vector(2, 3));

	ev.setObject1(&obj1);
	ev.setObject2(&obj2);
	ev.setPosition(df::Vector(2, 3));

	assert(ev.getObject1() == &obj1);
	assert(ev.getObject2() == &obj2);
	assert(ev.getPosition() == df::Vector(2, 3));

	printf("Test successful.\n");
	return 0;
}