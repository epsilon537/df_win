#include "Object.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
	df::Object obj1, obj2;

	printf("Obj1 id = %d\n", obj1.getId());
	printf("Obj2 id = %d\n", obj2.getId());

	obj1.setType("Test Object");
	assert(obj1.getType() == "Test Object");

	obj1.setPosition(df::Vector(4, 5));
	assert(obj1.getPosition() == df::Vector(4, 5));

	obj1.setAltitude(3);
	assert(obj1.getAltitude() == 3);

	obj1.setSpeed(4);
	assert(obj1.getSpeed() == 4);
	obj1.setDirection(df::Vector(1, 2));
	assert(obj1.getDirection() == df::Vector(1, 2).normalize());
	obj1.setPosition(df::Vector(1, 1));
	df::Vector v = obj1.predictPosition();
	assert(v == obj1.getPosition()+obj1.getVelocity());

	printf("velocity = %f,%f\n", obj1.getVelocity().getX(), obj1.getVelocity().getY());

	obj1.setVelocity(df::Vector(-2, 1));
	obj1.setPosition(df::Vector(1, 1));
	v = obj1.predictPosition();
	assert(v == df::Vector(-1, 2));

	printf("Test completed successfully.\n");

	return 0;
}