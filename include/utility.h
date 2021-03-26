#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Vector.h"
#include "Box.h"
#include <string>
#include "EventKeyboard.h"

namespace df {
	class Object;

	// Return  nicely-formatted time string: HH:MM:SS
	char* getTimeString();

	// Return true if two positions intersect.
	bool positionsIntersect(Vector p1, Vector p2);

	// Return true if boxes intersect.
	bool boxIntersectBox(Box a, Box b);

	// Convert relative bounding box for Object to absolute world box.
	Box getWorldBox(const Object* p_o);

	// Convert relative bounding box for Object to absolute world box at given position.
	Box getWorldBox(const Object* p_o, Vector where);

	// Return true if value is between min and max (inclusive).
	bool valueInRange(float value, float min, float max);

	// Return true if value is between min and max (inclusive).
	bool valueInRange(int value, int min, int max);

	// Return true if Box contains Position.
	bool boxContainsPosition(Box b, Vector p);

	// Return true if Box a completely contains Box b.
	bool boxContainsBox(Box a, Box b);

	// Return distance between any two positions.
	float distance(Vector p1, Vector p2);

	// Convert world position to view position.
	Vector worldToView(Vector world_pos);

	// Convert view position to world position.
	Vector viewToWorld(Vector view_pos);

	// Convert int to a string, returning string.
	std::string toString(int i);

	//Convert Keyboard code to string
	std::string toString(Keyboard::Key key);
}

#endif /*UTILITY_H*/