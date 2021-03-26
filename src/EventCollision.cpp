#include "EventCollision.h"

namespace df {
	// Default ctr, all members 0.
	EventCollision::EventCollision() : m_pos(), m_p_obj1(0), m_p_obj2(0) {
		setType(COLLISION_EVENT);
	}

	// Create collision event between o1 and o2 at position p.
	// o1 moved into o2.
	EventCollision::EventCollision(Object* p_o1, Object* p_o2, Vector p) : m_pos(p), m_p_obj1(p_o1), m_p_obj2(p_o2) {
		setType(COLLISION_EVENT);
	}

	// Set object that caused collision.
	void EventCollision::setObject1(Object* p_new_o1) {
		m_p_obj1 = p_new_o1;
	}

	// Return object that caused collision.
	Object* EventCollision::getObject1() const {
		return m_p_obj1;
	}

	// Set object that was collided with.
	void EventCollision::setObject2(Object* p_new_o2) {
		m_p_obj2 = p_new_o2;
	}

	// Return object that was collided with.
	Object* EventCollision::getObject2() const {
		return m_p_obj2;
	}

	// Set position of collision.
	void EventCollision::setPosition(Vector new_pos) {
		m_pos = new_pos;
	}

	// Return position of collision.
	Vector EventCollision::getPosition() const {
		return m_pos;
	}
}