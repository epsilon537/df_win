#ifndef __DF_OBJECT_H__
#define __DF_OBJECT_H__

#include <string>
#include "Vector.h"
#include "Animation.h"
#include "Box.h"

namespace df {
	class Event;

	const int MAX_OBJ_EVENTS = 100;
	
	enum Solidness {
		HARD, // Object causes collision and impedes movement.
		SOFT, // Object casues collisions but doesn't impede movement.
		SPECTRAL, // Object doesn't cause collisions.
	};

	class Object {
	private:
		int m_id;	//Unique game engine defined identifier.
		std::string m_type;	// Game programmer defined type.
		Vector m_position;	//Position in game world.
		int m_altitude; // 0 to MAX_ALTITUDE;
		Vector m_direction; // Direction vector.
		float m_speed; // Object speed in direction.
		Solidness m_solid; //Solidness of object.
		Animation m_animation; //Animation associated with Object.
		Box m_box; //Box for sprite boundary and collisions;
		int m_event_count;
		std::string m_event_name[MAX_OBJ_EVENTS];
		bool m_is_active; //If false, Object is not acted upon.

	public:
		//Default ctor sets default params and adds to game world (WorldManager).
		Object();

		//Destroy Object.
		//Remove from game world (WorldManager).
		virtual ~Object();

		// Set Object id.
		//void setId(int new_id);

		// Get Object id.
		int getId() const;

		// Set type id of Object.
		void setType(const std::string& new_type);

		// Get type id of Object.
		const std::string& getType() const;

		// Set position of Object. No movement is implied.
		void setPosition(const Vector& new_pos);

		// Get position of Object.
		Vector getPosition() const;

		// Handle event (default is to ignore everything).
		// Returns 0 if ignored, 1 if handled.
		virtual int eventHandler(const Event* p_e);

		// Draw Object Animation.
		// Returns 0 if OK, -1 on error.
		virtual int draw();

		// Set altitude of Object [0-MAX_ALTITUDE].
		// Return 0 if OK, -1 if out of range.
		int setAltitude(int new_altitude);

		// return object altitude
		int getAltitude() const;

		// Set speed of Object.
		void setSpeed(float speed);

		// Get speed of Object.
		float getSpeed() const;

		// Set direction of Object.
		void setDirection(Vector new_direction);

		// Get direction of Object.
		Vector getDirection() const;

		// Set velocity (direction and speed) of Object.
		void setVelocity(Vector new_velocity);

		// Get velocity of Object based on direction and speed.
		Vector getVelocity() const;

		// Predict Object position based on speed and direction.
		// Return predicted position.
		Vector predictPosition();

		// True if HARD or SOFT, else false.
		bool isSolid() const;

		// Set object solidness, with consistency checks.
		// return 0 if ok, else -1.
		int setSolidness(Solidness new_solid);

		// Return object solidness.
		Solidness getSolidness() const;

		//Set Sprite for this Object to animate;
		//Return 0 if ok, else -1.
		int setSprite(std::string sprite_label);

		//Set Animation for this Object to new one.
		//Set bounding box to size of associated Sprite.(TBD)
		void setAnimation(const Animation& new_animation);

		//Get Animation for this Object.
		Animation& getAnimation();

		//Set Object's bounding box.
		//IMPORTANT: Box coordinates are relative to the object, not the world!
		void setBox(Box box);

		//Get Object's bounding box.
		//IMPORTANT: Box coordinates are relative to the object, not the world!
		Box getBox() const;

		//Register for interest in event.
		//Keeps track of manager and event.
		//Return 0 if ok, else -1.
		int registerInterest(std::string event_type);

		//Unregister for interest in event.
		//Return 0 if ok, else -1.
		int unregisterInterest(std::string event_type);

		//Set activesness of Object. Objects not active are not acted upon by engine.
		//Return 0 if ok, else -1.
		int setActive(bool active = true);

		//Return activeness of Object. Objects not active are not acted upon by engine.
		bool isActive() const;
	};
}

#endif /*DF_OBJECT_H*/