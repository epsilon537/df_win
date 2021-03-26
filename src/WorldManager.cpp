#include "WorldManager.h"
#include "DisplayManager.h"
#include "ObjectListIterator.h"
#include "ObjectList.h"
#include "utility.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "EventKeyboard.h"
#include "EventStep.h"
#include "EventMouse.h"
#include "LogManager.h"
#include <assert.h>
#include "ViewObject.h"

namespace df {
	WorldManager::WorldManager() : m_scenegraph(), m_deletions(), m_boundary(), m_view(), m_view_following() {
		setType("WorldManager");
	}

	//Get the one and only instance of the WorldManager.
	WorldManager& WorldManager::getInstance() {
		static WorldManager worldManager;
		return worldManager;
	}

	//Startup game world (init everything to empty).
	//Return 0.
	int WorldManager::startUp() {
		m_scenegraph.clear();
		m_deletions.clear();
		return 0;
	}

	//Shutdown game world (delete all game world Objects).
	void WorldManager::shutDown() {
		ObjectList ol = getAllObjects(true); //copy so can delete during iteration.
		ObjectListIterator li(&ol);

		for (li.first(); !li.isDone(); li.next())
			delete li.currentObject();

		Manager::shutDown();
	}

	//Insert Object into world. Return 0 if ok, else -1.
	int WorldManager::insertObject(Object* p_o) {
		return m_scenegraph.insertObject(p_o);
	}

	//Remove Object from world. Return 0 if ok, else -1.
	int WorldManager::removeObject(Object* p_o) {
		return m_scenegraph.removeObject(p_o);
	}

	//Return list of all Objects in world.
	ObjectList WorldManager::getAllObjects(bool inclInactive) const {
		if (inclInactive) {
			return m_scenegraph.activeObjects() + m_scenegraph.inactiveObjects();
		}
		else {
			return m_scenegraph.activeObjects();
		}
	}

	//Return list of all Objects in world matching type.
	ObjectList WorldManager::objectsOfType(const std::string& type) const {
		ObjectList list, activeObjects = m_scenegraph.activeObjects();
		int res;
		Object* obj;

		ObjectListIterator li(&activeObjects);
		for (li.first(); !li.isDone(); li.next()) {
			obj = li.currentObject();
			assert(obj);

			if (obj->getType() == type) {
				res = list.insert(obj);
				assert(res == 0);
			}
		}

		return list;
	}

	// Update world.
	// Delete Objects marked for deletion.
	void WorldManager::update() {
		//Delete all marked objects.
		ObjectListIterator li(&m_deletions);
		while (!li.isDone()) {
			delete li.currentObject();
			li.next();
		}

		//Clear deletions list for next update.
		m_deletions.clear();

		ObjectList activeObjects = m_scenegraph.activeObjects();

		li.reassign(&activeObjects);
		for (li.first(); !li.isDone(); li.next()) {
			Object *obj = li.currentObject();
			assert(obj);
			Vector new_pos = obj->predictPosition();

			// If position changed, move
			if (new_pos != obj->getPosition())
				moveObject(obj, new_pos);
		}
	}

	//Indicate Object is to be deleted at end of current game loop.
	//Return 0 if ok, else -1.
	int WorldManager::markForDelete(Object* p_o) {
		//Only add once.
		ObjectListIterator li(&m_deletions);
		while (!li.isDone()) {
			if (li.currentObject() == p_o)
				return 0;

			li.next();
		}

		//Not in list yet, so add.
		return m_deletions.insert(p_o);
	}

	//Draw all objects.
	void WorldManager::draw() {
		int res;
		ObjectList visibleObjects;

		for (int alt=0; alt<=MAX_ALTITUDE; alt++) {
			visibleObjects = m_scenegraph.visibleObjects(alt);
			ObjectListIterator li(&visibleObjects);
			while (!li.isDone()) {
				Object* p_temp_o = li.currentObject();
				assert(p_temp_o);
				
				//Bounding box coordinates are relative to Object
				//so convert to world coordinates.
				Box temp_box = getWorldBox(p_temp_o);

				//Only draw if Object would be visible on window (intersects view)
				if (boxIntersectBox(temp_box, m_view) || //Object is in view
					dynamic_cast<ViewObject*>(p_temp_o)) { //or Object is ViewObject
					res = p_temp_o->draw();
					assert(res == 0);
				}
				
				li.next();
			}
		}
	}

	//Return list of objects collided with, if p_o were to move to 'where'.
	//Collision only with solid objects.
	//Does not consider if p_o itself is solid or not.
	ObjectList WorldManager::getCollisions(Object* p_o, Vector where) const {
		// Make empty list
		ObjectList collisions_list, solidObjects = m_scenegraph.solidObjects();

		//Iterate through all objects.
		ObjectListIterator li(&solidObjects);

		while (!li.isDone()) {
			Object* p_temp_o = li.currentObject();
			assert(p_temp_o);

			//Do not consider self
			if (p_temp_o != p_o) {
				//World position bounding box for object at where
				Box b = getWorldBox(p_o, where);

				//World position bounding box for other object
				Box b_temp = getWorldBox(p_temp_o);

				//Overlapping location?
				if (boxIntersectBox(b, b_temp)) {
					collisions_list.insert(p_temp_o);
				}
			}

			li.next();
		}

		return collisions_list;
	}

	//Move object
	// If collision with solid, send collision events.
	// If no collision with solid, move ok, else don't move.
	// If object is spectral, move ok.
	// Return 0 if move ok, else -1.
	int WorldManager::moveObject(Object* p_o, Vector where) {
		assert(p_o);

		if (p_o->isSolid()) { //Only solids can collide.
			//Get collisions
			ObjectList list = getCollisions(p_o, where);

			if (!list.isEmpty()) {
				bool do_move = true; //Assume we can move.

				//Iterate over list.
				ObjectListIterator li(&list);
				while (!li.isDone()) {
					Object* p_temp_o = li.currentObject();
					assert(p_temp_o);

					//Create collision event.
					EventCollision c(p_o, p_temp_o, where);

					//Send to both objects. Note that this does not go through onEvent so there's no event filtering.
					p_o->eventHandler(&c);
					p_temp_o->eventHandler(&c);

					//If both HARD, then can't move.
					if ((p_o->getSolidness() == HARD) &&
						(p_temp_o->getSolidness() == HARD))
						do_move = false;
					li.next();
				} //End iteration.

				if (!do_move)
					return -1; //Move not allowed.
			} //No collisions
		} //Object not solid.

		//No collision between HARD objects, so can move.
		df::Vector cur_position = p_o->getPosition();

		// Do move.
		Box orig_box = getWorldBox(p_o); //original bounding box
		p_o->setPosition(where); //move object
		Box new_box = getWorldBox(p_o); //new bounding box
		
		//EventOut handling
		if (boxIntersectBox(orig_box, m_boundary) && //Was in bounds...
			!boxIntersectBox(new_box, m_boundary)) {  //But not anymore...
			EventOut eo;
			//Also here, onEvent is not used, so no event filtering.
			p_o->eventHandler(&eo);
		}

		// If view is following this object, adjust view.
		if (m_view_following == p_o) {
			setViewPosition(p_o->getPosition());
		}

		return 0;
	}

	//Set game world boundary
	void WorldManager::setBoundary(Box new_boundary) {
		m_boundary = new_boundary;
	}

	//Get game world boundary.
	Box WorldManager::getBoundary() const {
		return m_boundary;
	}

	//Set player view of world.
	void WorldManager::setView(Box new_view) {
		m_view = new_view;
	}

	//Get player view of world.
	Box WorldManager::getView() const {
		return m_view;
	}

	// Set view to center window on given position.
	// View edge will not go beyond world boundary.
	void WorldManager::setViewPosition(Vector view_pos) {
		//Clamp to world boundaries
		float x = view_pos.getX() - m_view.getHorizontal() / 2;

		if (x + m_view.getHorizontal() > m_boundary.getHorizontal()) {
			x = m_boundary.getHorizontal() - m_view.getHorizontal();
		}
		if (x < 0) {
			x = 0;
		}

		float y = view_pos.getY() - m_view.getVertical() / 2;

		if (y + m_view.getVertical() > m_boundary.getVertical()) {
			y = m_boundary.getVertical() - m_view.getVertical();
		}
		if (y < 0) {
			y = 0;
		}

		// Set view.
		Vector new_corner(x, y);
		m_view.setCorner(new_corner);
	}

	// Set view to center window on Object.
	// Set to NULL to stop following.
	// Return -1 if object not legit.
	int WorldManager::setViewFollowing(Object* p_new_following) {
		if (p_new_following == 0) {
			m_view_following = 0;
			return 0;
		}

		ObjectList ol = m_scenegraph.activeObjects();
		ObjectListIterator li(&ol);

		//Iterate over all objects. Make sure p_new_following
		//is one of the objects.
		bool found = false;
		for (li.first(); !li.isDone(); li.next()) {
			if (li.currentObject() == p_new_following) {
				found = true;
				break;
			}
		}

		if (found) {
			m_view_following = p_new_following;
			setViewPosition(p_new_following->getPosition());
			return 0;
		}

		return -1; //Object not legit.
	}

	bool WorldManager::isValid(std::string event_name) const {
		if (event_name == df::STEP_EVENT)
			return false;

		if (event_name == df::KEYBOARD_EVENT)
			return false;

		if (event_name == df::MSE_EVENT)
			return false;

		return true;
	}

	SceneGraph& WorldManager::getSceneGraph() {
		return m_scenegraph;
	}
}