#ifndef __DF_EVENT_COLLISION_H__
#define __DF_EVENT_COLLISION_H__

#include "Event.h"
#include "Object.h"

namespace df {
	const std::string COLLISION_EVENT = "df::collision";

	class EventCollision : public Event {
	private:
		Vector m_pos; // Where collision occured.
		Object* m_p_obj1; // Object moving causing the collision.
		Object* m_p_obj2; // Object collided with.
	public:
		// Default ctr, all members 0.
		EventCollision();

		// Create collision event between o1 and o2 at position p.
		// o1 moved into o2.
		EventCollision(Object* p_o1, Object* p_o2, Vector p);

		// Set object that caused collision.
		void setObject1(Object* p_new_o1);

		// Return object that caused collision.
		Object* getObject1() const;

		// Set object that was collided with.
		void setObject2(Object* p_new_o2);

		// Return object that was collided with.
		Object* getObject2() const;

		// Set position of collision.
		void setPosition(Vector new_pos);

		// Return position of collision.
		Vector getPosition() const;
	};
}

#endif /*EVENT_COLLISION_H*/