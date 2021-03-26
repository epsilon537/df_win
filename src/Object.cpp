#include "Object.h"
#include "Vector.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "SceneGraph.h"

namespace df {
	static int id_counter = 0;

	Vector m_direction; // Direction vector.
	float m_speed; // Object speed in direction.

	//Default ctor sets default params and adds to game world (WorldManager).
	//Note: default box is 1x1 in size.
	Object::Object() : m_id(id_counter++), m_type("Object"), m_position(), m_altitude(MAX_ALTITUDE / 2), 
		m_direction(1, 0), m_speed(0), m_solid(HARD), m_animation(), m_box(Vector(0,0), 1, 1), m_event_count(0), m_is_active(true) {
		//Add self to game world.
		WM.insertObject(this);
	}

	//Destroy Object.
	//Remove from game world (WorldManager).
	Object::~Object() {
		//Unregister from events
		for (int index = m_event_count - 1; index >= 0; index--) {
			unregisterInterest(m_event_name[index]);
		}

		//Remove self from game world.
		WM.removeObject(this);
	}

	// Set Object id.
	//void Object::setId(int new_id) {
	//	m_id = new_id;
	//}

	// Get Object id.
	int Object::getId() const {
		return m_id;
	}

	// Set type id of Object.
	void Object::setType(const std::string& new_type) {
		m_type = new_type;
	}

	// Get type id of Object.
	const std::string& Object::getType() const {
		return m_type;
	}

	// Set position of Object. No movement is implied.
	void Object::setPosition(const Vector& new_pos) {
		m_position = new_pos;
	}

	// Get position of Object.
	Vector Object::getPosition() const {
		return m_position;
	}

	// Handle event (default is to ignore everything).
	// Returns 0 if ignored, 1 if handled.
	int Object::eventHandler(const Event* p_e) {
		return 0;
	}

	// Draw self.
	// Returns 0 if OK, -1 on error.
	int Object::draw() {
		return m_animation.draw(m_position);
	}

	// Set altitude of Object [0-MAX_ALTITUDE].
		// Return 0 if OK, -1 if out of range.
	int Object::setAltitude(int new_altitude) {
		if ((new_altitude < 0) ||
			(new_altitude > MAX_ALTITUDE))
			return -1;

		//Update scenegraph and altitude
		int res = WM.getSceneGraph().updateAltitude(this, new_altitude);
		m_altitude = new_altitude;

		return res;
	}

	// return object altitude
	int Object::getAltitude() const {
		return m_altitude;
	}

	// Set speed of Object.
	void Object::setSpeed(float speed) {
		m_speed = speed;
	}

	// Get speed of Object.
	float Object::getSpeed() const {
		return m_speed;
	}

	// Set direction of Object.
	void Object::setDirection(Vector new_direction) {
		m_direction = new_direction.normalize();
	}

	// Get direction of Object.
	Vector Object::getDirection() const {
		return m_direction;
	}

	// Set velocity (direction and speed) of Object.
	void Object::setVelocity(Vector new_velocity) {
		m_speed = new_velocity.getMagnitude();
		m_direction = new_velocity.normalize();
	}

	// Get velocity of Object based on direction and speed.
	Vector Object::getVelocity() const {
		return m_direction * m_speed;
	}

	// Predict Object position based on speed and direction.
	// Return predicted position.
	Vector Object::predictPosition() {
		return m_position + getVelocity();
	}

	// True if HARD or SOFT, else false.
	bool Object::isSolid() const {
		return (m_solid == HARD) || (m_solid == SOFT);
	}

	// Set object solidness, with consistency checks.
	// return 0 if ok, else -1.
	int Object::setSolidness(Solidness new_solid) {
		if ((new_solid < HARD) || (new_solid > SPECTRAL))
			return -1;

		//Update scenegraph and solidness
		int res = WM.getSceneGraph().updateSolidness(this, new_solid);
		m_solid = new_solid;

		return res;
	}

	// Return object solidness.
	Solidness Object::getSolidness() const {
		return m_solid;
	}

	//Set Sprite for this Object to animate;
	//Return 0 if ok, else -1.
	int Object::setSprite(std::string sprite_label) {
		Sprite* p_sprite = RM.getSprite(sprite_label);
		if (!p_sprite)
			return -1;

		m_animation.setSprite(p_sprite);
		Box abox = m_animation.getBox();
		abox.setCorner(abox.getCorner() - Vector(abox.getHorizontal()/2, abox.getVertical()/2));
		setBox(abox);

		return 0;
	}

	//Set Animation for this Object to new one.
	//Set bounding box to size of associated Sprite.(TBD)
	void Object::setAnimation(const Animation& new_animation) {
		m_animation = new_animation;
		Box abox = m_animation.getBox();
		abox.setCorner(abox.getCorner() - Vector(abox.getHorizontal() / 2, abox.getVertical() / 2));
		setBox(abox);
	}

	//Get Animation for this Object.
	Animation& Object::getAnimation() {
		return m_animation;
	}

	//Set Object's bounding box.
	void Object::setBox(Box box) {
		m_box = box;
	}

	//Get Object's bounding box.
	Box Object::getBox() const {
		return m_box;
	}

	//Register for interest in event.
	//Keeps track of manager and event.
	//Return 0 if ok, else -1.
	int Object::registerInterest(std::string event_type) {
		//Check if room
		if (m_event_count >= MAX_OBJ_EVENTS)
			return -1;

		//Register with appropriate manager
		if (event_type == df::STEP_EVENT) {
			if (GM.registerInterest(this, event_type) == -1)
				return -1;
		}
		else if ((event_type == df::KEYBOARD_EVENT) || (event_type == df::MSE_EVENT)) {
			if (IM.registerInterest(this, event_type) == -1)
				return -1;
		}
		else {
			if (WM.registerInterest(this, event_type) == -1)
				return -1;
		}

		//Keep track of added event.
		m_event_name[m_event_count] = event_type;
		++m_event_count;

		return 0;
	}

	//Unregister for interest in event.
	//Return 0 if ok, else -1.
	int Object::unregisterInterest(std::string event_type) {
		for (int index = 0; index < m_event_count; index++) {
			if (m_event_name[index] == event_type) {
				//Unregister with appropriate manager
				if (event_type == df::STEP_EVENT) {
					if (GM.unregisterInterest(this, event_type) == -1)
						return -1;
				}
				else if ((event_type == df::KEYBOARD_EVENT) || (event_type == df::MSE_EVENT)) {
					if (IM.unregisterInterest(this, event_type) == -1)
						return -1;
				}
				else {
					if (WM.unregisterInterest(this, event_type) == -1)
						return -1;
				}

				//Scoot over all remaining items.
				for (int jj = index; jj < m_event_count - 1; jj++) {
					m_event_name[jj] = m_event_name[jj + 1];
				}

				--m_event_count;
				return 0;
			}
				
		}
		
		return -1;
	}

	//Set activesness of Object. Objects not active are not acted upon by engine.
	//Return 0 if ok, else -1.
	int Object::setActive(bool active) {
		//Update scene graph.
		int res = WM.getSceneGraph().updateActive(this, active);

		//Set active value;
		m_is_active = active;

		return res;
	}

	//Return activeness of Object. Objects not active are not acted upon by engine.
	bool Object::isActive() const {
		return m_is_active;
	}
}