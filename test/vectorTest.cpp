#include "Vector.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
	df::Vector v1;
	df::Vector v2(1, 2);

	assert(v1.getX() == 0);
	assert(v1.getY() == 0);
	assert(v2.getX() == 1);
	assert(v2.getY() == 2);

	v1 += v2;
	assert(v1.getX() == 1);
	assert(v1.getY() == 2);

	df::Vector v3(v1 + v2); //Copy constructor

	assert(v3.getX() == 2);
	assert(v3.getY() == 4);

	v3.normalize();
	printf("v3 magnitude after normalize: %f\n", v3.getMagnitude());

	v3.setX(1);
	v3.setY(2);

	assert(v3.getX() == 1);
	assert(v3.getY() == 2);

	v3.setXY(4, 5);
	assert(v3.getX() == 4);
	assert(v3.getY() == 5);
	printf("Magnitude of (4,5): %f\n", v3.getMagnitude());
	
	df::Vector v4(v3);
	df::Vector v5 = v3 * 0.5;
	df::Vector v6 = v3;

	v3.scale(0.5);
	assert(v3.getX() == 2.0);
	assert(v3.getY() == 2.5);

	v4 *= 0.5;
	assert(v4 == v3);
	assert(v5 == v3);

	assert(v6.scale(0.5).getX() == 2.0);
	assert(v6.normalize().getMagnitude() == 1);

	v3 = df::Vector();
	assert(v3.getX() == 0);
	assert(v3.getY() == 0);
	

	v1 -= v1;
	assert(v1.getX() == 0);
	assert(v1.getY() == 0);

	v1 = v2;
	assert(v1 == v2);
	v1 += v2;
	assert(v1 != v2);

	v3.setXY(4, 5);
	v2.setXY(1, 1);
	v1 = v3 - v2;
	assert(v1.getX() == 3);
	assert(v1.getY() == 4);

	printf("Test completed successfully\n");

	return 0;
}