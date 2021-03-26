#include "Box.h"

namespace df {
	//Create box with (0,0) for all params.
	Box::Box() : m_corner(), m_horizontal(0), m_vertical(0) {

	}

	//Create box with given params
	Box::Box(Vector init_corner, float init_horizontal, float init_vertical) : m_corner(init_corner), m_horizontal(init_horizontal), m_vertical(init_vertical) {
	}

	//Set upper left corner of box.
	void Box::setCorner(Vector new_corner) {
		m_corner = new_corner;
	}

	//Get upper left corner of box.
	Vector Box::getCorner() const {
		return m_corner;
	}

	//Set horizontal size of box.
	void Box::setHorizontal(float new_horizontal) {
		m_horizontal = new_horizontal;
	}

	//Get horizontal size of box.
	float Box::getHorizontal() const {
		return m_horizontal;
	}


	//Set vertical size of box.
	void Box::setVertical(float new_vertical) {
		m_vertical = new_vertical;
	}

	//Get vertical size of box.
	float Box::getVertical() const {
		return m_vertical;
	}

	//Compare to boxes for equality
	bool Box::operator==(const Box& other) {
		return (m_corner == other.m_corner) && (m_horizontal == other.m_horizontal) && (m_vertical == other.m_vertical);
	}

	//Compare to boxes for inequality2
	bool Box::operator!=(const Box& other) {
		return !(*this == other);
	}
}