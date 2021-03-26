#ifndef __DF_SCENE_GRAPH_H__
#define __DF_SCENE_GRAPH_H__

#include "Object.h"
#include "ObjectList.h"

namespace df {
	const int MAX_ALTITUDE = 4;

	class SceneGraph {
	private:
		ObjectList m_active_objects; //Active objects.
		ObjectList m_inactive_objects; //Inactive objectd.
		ObjectList m_solid_objects; //Solid objects.
		ObjectList m_visible_objects[MAX_ALTITUDE + 1]; //Visible objects.

	public:
		SceneGraph();
		~SceneGraph();

		//Insert Object into SceneGraph. Return 0 if ok, -1 if error.
		int insertObject(Object* p_o);

		//Remove Object from SceneGraph.
		int removeObject(Object* p_o);

		//Clear all objects from the SceneGraph.
		void clear();

		//Return all active Objects. Empty list if none.
		ObjectList activeObjects() const;

		//Return all solid Objects. Empty list if none.
		ObjectList solidObjects() const;

		//Return all active, visible Objects at altitude. Empty list if none.
		ObjectList visibleObjects(int altitude) const;

		//Return all inactive Objects. Empty list if none.
		ObjectList inactiveObjects() const;

		//Re-position Object in SceneGraph to new altitude.
		//Return 0 if ok, else -1.
		int updateAltitude(Object* p_o, int new_alt);

		//Re-position Object in SceneGraph to new solidness.
		//Return 0 if ok, else -1.
		int updateSolidness(Object* p_o, Solidness new_solidness);

		//Re-position Object in SceneGraph to new activeness.
		//Return 0 if ok, else -1.
		int updateActive(Object* p_o, bool new_active);
	};
}

#endif /*DF_SCENE_GRAPH*/
