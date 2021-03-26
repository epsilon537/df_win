#include "WorldManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"

#include <stdio.h>
#include <assert.h>

class TestObject : public df::Object {
private:
public:
	TestObject();

	~TestObject();
};

TestObject::TestObject() {
	setType("TestObject");
}

TestObject::~TestObject() {
	
	printf("TestObject %d deleted.\n", getId());
}

int main(void) {
	TestObject* objs[5];
	int ii;
	int res = WM.startUp();
	assert(res == 0);
	assert(!WM.isStarted());

	for (ii = 0; ii < 5; ii++) {
		objs[ii] = new TestObject;
	}

	df::ObjectList objList = WM.getAllObjects();
	df::ObjectListIterator li(&objList);

	ii = 0;
	while (!li.isDone()) {
		assert(ii < 5);
		assert(li.currentObject());
		assert(objs[ii]);
		printf("Current Obj.id=%d\n", li.currentObject()->getId());
		printf("obj[%d]->id=%d\n", ii, objs[ii]->getId());
		assert(li.currentObject()->getId() == objs[ii]->getId());
		++ii;
		li.next();
	}

	objs[1]->setType("Test2");
	objs[3]->setType("Test2");

	objList = WM.objectsOfType("Test2");
	li.reassign(&objList);

	assert(li.currentObject());
	assert(li.currentObject()->getId() == objs[1]->getId());
	li.next();
	assert(li.currentObject());
	assert(li.currentObject()->getId() == objs[3]->getId());
	li.next();

	printf("Marking obj.3 and 1 for delete.\n");
	WM.markForDelete(objs[3]);
	WM.markForDelete(objs[1]);

	printf("Updating WM.\n");
	WM.update();

	printf("Updating WM again (should have no effect).\n");
	WM.update();

	printf("Shuttding down WM.\n");
	WM.shutDown();
	assert(!WM.isStarted());

	printf("Test Completed.\n");

	return 0;
}