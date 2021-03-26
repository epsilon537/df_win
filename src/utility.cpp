#include "utility.h"
#include "Object.h"
#include "WorldManager.h"

#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <cmath>
#include <sstream>

namespace df {
	char* getTimeString() {
		int res;

		// String to return, made 'state' so persists.
		static char time_str[30];

		// System call to get time.
		time_t now;
		time_t time_res = time(&now);
		assert(time_res != -1);

		struct tm* p_time = localtime(&now);
		assert(p_time);

		// '02' gives two digits, '%d' for integers.
		res = snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d",
			p_time->tm_hour,
			p_time->tm_min,
			p_time->tm_sec);
		assert(res > 0);

		return time_str;
	}

	bool positionsIntersect(Vector p1, Vector p2) {
		return (std::abs(p1.getX() - p2.getX()) <= 1) && (std::abs(p1.getY() - p2.getY()) <= 1);
	}

	// Return true if boxes intersect.
	bool boxIntersectBox(Box a, Box b) {
		Vector aCorner = a.getCorner();
		Vector bCorner = b.getCorner();
		float ax1 = aCorner.getX();
		float bx1 = bCorner.getX();
		float ay1 = aCorner.getY();
		float by1 = bCorner.getY();
		float ax2 = ax1 + a.getHorizontal();
		float bx2 = bx1 + b.getHorizontal();
		float ay2 = ay1 + a.getVertical();
		float by2 = by1 + b.getVertical();

		//Test horizontal overlap
		bool x_overlap = (
			((bx1 <= ax1) && (ax1 <= bx2)) ||
			((ax1 <= bx1) && (bx1 <= ax2)));

		//Test vertical overlap
		bool y_overlap = (
			((by1 <= ay1) && (ay1 <= by2)) ||
			((ay1 <= by1) && (by1 <= ay2)));

		return x_overlap && y_overlap;
	}

	// Convert relative bounding box for Object to absolute world box.
	Box getWorldBox(const Object* p_o) {
		assert(p_o);

		return getWorldBox(p_o, p_o->getPosition());
	}

	// Convert relative bounding box for Object to absolute world box at given position.
	Box getWorldBox(const Object* p_o, Vector where) {
		assert(p_o);

		Box box = p_o->getBox();
		box.setCorner(box.getCorner() + where);

		return box;
	}

	// Return true if value is between min and max (inclusive).
	bool valueInRange(float value, float min, float max) {
		return (value >= min) && (value <= max);
	}

	// Return true if value is between min and max (inclusive).
	bool valueInRange(int value, int min, int max) {
		return (value >= min) && (value <= max);
	}

	// Return true if Box contains Position.
	bool boxContainsPosition(Box b, Vector p) {
		Vector bCorner = b.getCorner();
		float bx1 = bCorner.getX();
		float by1 = bCorner.getY();
		float bx2 = bx1 + b.getHorizontal();
		float by2 = by1 + b.getVertical();

		//Test horizontal overlap
		bool x_overlap = valueInRange(p.getX(), bx1, bx2);

		//Test vertical overlap
		bool y_overlap = valueInRange(p.getY(), by1, by2);

		return x_overlap && y_overlap;
	}

	// Return true if Box a completely contains Box b.
	bool boxContainsBox(Box a, Box b) {
		Vector aCorner = a.getCorner();
		Vector bCorner = b.getCorner();
		float ax1 = aCorner.getX();
		float bx1 = bCorner.getX();
		float ay1 = aCorner.getY();
		float by1 = bCorner.getY();
		float ax2 = ax1 + a.getHorizontal();
		float bx2 = bx1 + b.getHorizontal();
		float ay2 = ay1 + a.getVertical();
		float by2 = by1 + b.getVertical();

		bool x_overlap = (ax1 <= bx1) && (ax2 >= bx2);
		bool y_overlap = (ay1 <= by1) && (ay2 >= by2);

		return x_overlap && y_overlap;
	}

	// Return distance between any two positions.
	float distance(Vector p1, Vector p2) {
		Vector diff = p2 - p1;
		return diff.getMagnitude();
	}

	// Convert world position to view position.
	Vector worldToView(Vector world_pos) {
		Vector view_origin = WM.getView().getCorner();
		return world_pos - view_origin;
	}

	// Convert view position to world position.
	Vector viewToWorld(Vector view_pos) {
		Vector view_origin = WM.getView().getCorner();

		return view_pos + view_origin;
	}

	// Convert int to a string, returning string.
	std::string toString(int i) {
		std::stringstream ss; //Create stringstream.
		ss << i; //Add number to stream.
		return ss.str(); //Return string with contents of stream.
	}

	std::string toString(Keyboard::Key key) {
		switch (key) {
		case Keyboard::A: return std::string("A");
		case Keyboard::B: return std::string("B");
		case Keyboard::C: return std::string("C");
		case Keyboard::D: return std::string("D");
		case Keyboard::E: return std::string("E");
		case Keyboard::F: return std::string("F");
		case Keyboard::G: return std::string("G");
		case Keyboard::H: return std::string("H");
		case Keyboard::I: return std::string("I");
		case Keyboard::J: return std::string("J");
		case Keyboard::K: return std::string("K");
		case Keyboard::L: return std::string("L");
		case Keyboard::M: return std::string("M");
		case Keyboard::N: return std::string("N");
		case Keyboard::O: return std::string("O");
		case Keyboard::P: return std::string("P");
		case Keyboard::Q: return std::string("Q");
		case Keyboard::R: return std::string("R");
		case Keyboard::S: return std::string("S");
		case Keyboard::T: return std::string("T");
		case Keyboard::U: return std::string("U");
		case Keyboard::V: return std::string("V");
		case Keyboard::W: return std::string("W");
		case Keyboard::X: return std::string("X");
		case Keyboard::Y: return std::string("Y");
		case Keyboard::Z: return std::string("Z");
		case Keyboard::NUM0: return std::string("0");
		case Keyboard::NUM1: return std::string("1");
		case Keyboard::NUM2: return std::string("2");
		case Keyboard::NUM3: return std::string("3");
		case Keyboard::NUM4: return std::string("4");
		case Keyboard::NUM5: return std::string("5");
		case Keyboard::NUM6: return std::string("6");
		case Keyboard::NUM7: return std::string("7");
		case Keyboard::NUM8: return std::string("8");
		case Keyboard::NUM9: return std::string("9");
		case Keyboard::COMMA: return std::string(",");
		case Keyboard::PERIOD: return std::string(".");
		case Keyboard::SLASH: return std::string("/");
		case Keyboard::TILDE: return std::string("~");
		case Keyboard::SPACE: return std::string(" ");
		case Keyboard::PLUS: return std::string("+");
		case Keyboard::MINUS: return std::string("-");
		default: return std::string(" ");
		}
	}
}