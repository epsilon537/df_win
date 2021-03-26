#include "GameManager.h"
#include "LogManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "SceneGraph.h"
#include "WorldManager.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
	GM.startUp();
	LM.setLogToScreen();

	df::Object* obj1 = new df::Object();
	df::Object* obj2 = new df::Object();

	df::SceneGraph& sg = WM.getSceneGraph();
	df::ObjectList ol = sg.activeObjects();
	assert(ol == WM.getAllObjects());

	df::ObjectListIterator iter(&ol);
	
	iter.first();
	assert(iter.currentObject() == obj1);
	iter.next();
	assert(iter.currentObject() == obj2);
	iter.next();
	assert(iter.isDone());

	WM.removeObject(obj1);

	ol = sg.activeObjects();
	iter.reassign(&ol);

	iter.first();
	assert(iter.currentObject() == obj2);
	iter.next();
	assert(iter.isDone());

	WM.removeObject(obj2);

	WM.insertObject(obj1);
	WM.insertObject(obj2);

	int res = obj1->setSolidness(df::SOFT);
	assert(res == 0);

	res = obj1->setAltitude(1);
	assert(res == 0);

	res = obj2->setSolidness(df::SPECTRAL);
	assert(res == 0);

	res = obj2->setAltitude(2);
	assert(res == 0);

	ol = sg.solidObjects();
	iter.reassign(&ol);

	iter.first();
	assert(iter.currentObject() == obj1);
	iter.next();
	assert(iter.isDone());

	ol = sg.visibleObjects(1);
	iter.reassign(&ol);

	iter.first();
	assert(iter.currentObject() == obj1);
	iter.next();
	assert(iter.isDone());

	ol = sg.visibleObjects(2);
	iter.reassign(&ol);

	iter.first();
	assert(iter.currentObject() == obj2);
	iter.next();
	assert(iter.isDone());

	WM.removeObject(obj2);
	WM.removeObject(obj1);

	assert(sg.visibleObjects(1).isEmpty());
	assert(sg.visibleObjects(2).isEmpty());
	assert(sg.solidObjects().isEmpty());

	GM.shutDown();
	printf("Test done.\n");
	return 0;
}