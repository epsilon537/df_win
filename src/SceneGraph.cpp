#include "SceneGraph.h"
#include "utility.h"
#include "WorldManager.h"
#include "LogManager.h"
#include <assert.h>

namespace df {
	SceneGraph::SceneGraph() {
	}

	SceneGraph::~SceneGraph() {
	}

	//Insert Object into SceneGraph. 
	int SceneGraph::insertObject(Object* p_o) {
		assert(p_o);

		//Add object to active/inActive list.
		if (p_o->isActive()) {
			if (m_active_objects.insert(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph active objects list.\n");
				return -1;
			}
		}
		else {
			if (m_inactive_objects.insert(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph inactive objects list.\n");
				return -1;
			}
		}

		//If solid, add to solid objects list.
		if (p_o->isSolid()) {
			if (m_solid_objects.insert(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph solid_objects list.\n");
				return -1;
			}
		}

		//Check altitude
		assert(valueInRange(p_o->getAltitude(), 0, MAX_ALTITUDE));

		//Add to visible objects at right altitude.
		if (m_visible_objects[p_o->getAltitude()].insert(p_o) == -1) {
			LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph visible_objects list.\n");
			return -1;
		}

		return 0;
	}

	//Remove Object from SceneGraph.
	int SceneGraph::removeObject(Object* p_o) {
		assert(p_o);

		if (p_o->isActive()) {
			if (m_active_objects.remove(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to remove object from SceneGraph active objects list (1).\n");
			}
		}
		else {
			if (m_inactive_objects.remove(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to remove object from SceneGraph inactive objects list (1).\n");
			}
		}

		if (p_o->isSolid()) {
			if (m_solid_objects.remove(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to remove object from SceneGraph solid_objects list (1).\n");
				return -1;
			}
		}

		if (m_visible_objects[p_o->getAltitude()].remove(p_o) == -1) {
			LM.writeLog(IMPORTANT_LVL, "Failed to remove object from SceneGraph visible_objects list (1).\n");
			return -1;
		}

		return 0;
	}

	//Return all active Objects. Empty list if none.
	ObjectList SceneGraph::activeObjects() const {
		return m_active_objects;
	}

	//Return all solid Objects. Empty list if none.
	ObjectList SceneGraph::solidObjects() const {
		return m_solid_objects;
	}

	//Return all active, visible Objects at altitude. Empty list if none.
	ObjectList SceneGraph::visibleObjects(int altitude) const {
		//Check altitude
		assert(valueInRange(altitude, 0, MAX_ALTITUDE));

		return m_visible_objects[altitude];
	}

	//Return all inactive Objects. Empty list if none.
	ObjectList SceneGraph::inactiveObjects() const {
		return m_inactive_objects;
	}

	//Re-position Object in SceneGraph to new altitude.
	//Return 0 if ok, else -1.
	int SceneGraph::updateAltitude(Object* p_o, int new_alt) {
		assert(p_o);

		//Check altitude
		assert(valueInRange(new_alt, 0, MAX_ALTITUDE));

		//Remove from old altitude.
		if (m_visible_objects[p_o->getAltitude()].remove(p_o) == -1) {
			LM.writeLog(IMPORTANT_LVL, "Failed to remove object into SceneGraph visible_objects list.\n");
			return -1;
		}

		//Add to new altitude.
		if (m_visible_objects[new_alt].insert(p_o) == -1) {
			LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph visible_objects list.\n");
			return -1;
		}

		return 0;
	}

	//Re-position Object in SceneGraph to new solidness.
	//Return 0 if ok, else -1.
	int SceneGraph::updateSolidness(Object* p_o, Solidness new_solidness) {
		assert(p_o);
		//If was solid, remove from solid objects list.
		if (p_o->isSolid()) {
			if (m_solid_objects.remove(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to remove object from SceneGraph solid_objects list.\n");
				return -1;
			}
		}

		//If solid, add to solid objects list.
		if ((new_solidness == HARD) || (new_solidness == SOFT)) {
			if (m_solid_objects.insert(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph solid_objects list.\n");
				return -1;
			}
		}

		return 0;
	}

	//Re-position Object in SceneGraph to new activeness.
	//Return 0 if ok, else -1.
	int SceneGraph::updateActive(Object* p_o, bool new_active) {
		assert(p_o);

		//If activeness unchanged, nothing to do (but ok).
		if (p_o->isActive() == new_active) {
			return 0;
		}
		
		//If was active then now inactive, so remove from lists.
		if (p_o->isActive()) {
			if (m_active_objects.remove(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to remove object from SceneGraph active objects list (2).\n");
				return -1;
			}

			if (m_visible_objects[p_o->getAltitude()].remove(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to remove object into SceneGraph visible_objects list (2).\n");
				return -1;
			}

			if (p_o->isSolid()) {
				if (m_solid_objects.remove(p_o) == -1) {
					LM.writeLog(IMPORTANT_LVL, "Failed to remove object from SceneGraph solid_objects list (2).\n");
					return -1;
				}
			}

			//Add to inactive list.
			if (m_inactive_objects.insert(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph inactive objects list.\n");
				return -1;
			}
		}
		else { //Was inactive, so add to lists.
			//Add object to list.
			if (m_active_objects.insert(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph active_objects list.\n");
				return -1;
			}

			//If solid, add to solid objects list.
			if (p_o->isSolid()) {
				if (m_solid_objects.insert(p_o) == -1) {
					LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph solid_objects list.\n");
					return -1;
				}
			}

			//Check altitude
			assert(valueInRange(p_o->getAltitude(), 0, MAX_ALTITUDE));

			//Add to visible objects at right altitude.
			if (m_visible_objects[p_o->getAltitude()].insert(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to insert object into SceneGraph visible_objects list.\n");
				return -1;
			}

			//Remove from inactive list.
			if (m_inactive_objects.remove(p_o) == -1) {
				LM.writeLog(IMPORTANT_LVL, "Failed to remove object from SceneGraph inactive objects list (2).\n");
				return -1;
			}
		}

		return 0;
	}

	//Clear all objects from the SceneGraph.
	void SceneGraph::clear() {
		m_active_objects.clear();
		m_solid_objects.clear();
		
		for (int ii = 0; ii <= MAX_ALTITUDE; ii++) {
			m_visible_objects[ii].clear();
		}
	}
}