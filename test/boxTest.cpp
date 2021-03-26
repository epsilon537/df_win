#include "Box.h"
#include "Vector.h"
#include <stdio.h>
#include <assert.h>
#include "utility.h"

int main(void) {
	df::Box box1;
	assert(box1.getCorner() == df::Vector(0, 0));
	assert(box1.getHorizontal() == 0);
	assert(box1.getVertical() == 0);

	df::Box box2(df::Vector(3, 2), 100, 200);
	assert(box2.getCorner() == df::Vector(3, 2));
	assert(box2.getHorizontal() == 100);
	assert(box2.getVertical() == 200);

	box2.setCorner(df::Vector(10, 20));
	box2.setHorizontal(1000);
	box2.setVertical(2000);

	assert(box2.getCorner() == df::Vector(10, 20));
	assert(box2.getHorizontal() == 1000);
	assert(box2.getVertical() == 2000);

	box1 = df::Box(df::Vector(-1, -2), 3, 4);
	box2 = df::Box(df::Vector(2, 2), 5, 6);

	assert(boxIntersectBox(box1, box2) == false);
	
	box2.setCorner()
	printf("Test Complete.\n");
	return 0;
}