#ifndef __DF_WORLD_MANAGER_H__
#define __DF_WORLD_MANAGER_H__

#include "Manager.h"
#include "ObjectList.h"
#include "Box.h"
#include "SceneGraph.h"

// Two-letter acronym for easier access to manager.
#define WM df::WorldManager::getInstance()

namespace df {
	class WorldManager : public Manager {
	private:
		WorldManager();
		WorldManager(WorldManager const&);
		void operator=(WorldManager const&);

		SceneGraph m_scenegraph;
		ObjectList m_deletions; //All Objects in worls to delete.
		Box m_boundary; //World boundary
		Box m_view; //Player view of game world.
		Object* m_view_following; //Object view is following.

	public:
		//Get the one and only instance of the WorldManager.
		static WorldManager& getInstance();

		//Startup game world (init everything to empty).
		//Return 0.
		int startUp();

		//Shutdown game world (delete all game world Objects).
		void shutDown();

		//Insert Object into world. Return 0 if ok, else -1.
		int insertObject(Object* p_o);

		//Remove Object from world. Return 0 if ok, else -1.
		int removeObject(Object* p_o);

		//Return list of all Objects in world.
		//If inclInActive is true, include inactive objects.
		ObjectList getAllObjects(bool inclInactive=false) const;

		//Return list of all Objects in world matching type.
		ObjectList objectsOfType(const std::string& type) const;

		// Update world.
		// Delete Objects marked for deletion.
		void update();

		//Indicate Object is to be deleted at end of current game loop.
		//Return 0 if ok, else -1.
		int markForDelete(Object* p_0);

		//Draw all objects.
		void draw();

		//Return list of objects collided with, if p_o were to move to 'where'.
		//Collision only with solid objects.
		//Does not consider if p_o itself is solid or not.
		ObjectList getCollisions(Object* p_o, Vector where) const;

		//Move object
		// If collision with solid, send collision events.
		// If no collision with solid, move ok, else don't move.
		// If object is spectral, move ok.
		// Return 0 if move ok, else -1.
		int moveObject(Object* p_o, Vector where);

		//Set game world boundary
		void setBoundary(Box new_boundary);

		//Get game world boundary.
		Box getBoundary() const;

		//Set player view of world.
		void setView(Box new_view);

		//Get player view of world.
		Box getView() const;

		// Set view to center window on given position (in world coordinates).
		// View edge will not go beyond world boundary.
		void setViewPosition(Vector view_pos);

		// Set view to center window on Object.
		// Set to NULL to stop following.
		// Return -1 if object not legit.
		int setViewFollowing(Object* p_new_following);

		//Indicate which type of events this manager supports.
		bool isValid(std::string event_name) const;

		//Return reference to the SceneGraph
		SceneGraph& getSceneGraph();
	};
}

#endif /*DF_WORLD_MANAGER_H*/
