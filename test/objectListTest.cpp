#include "ObjectList.h"
#include <assert.h>
#include <stdio.h>

df::ObjectList objList;

int main(void) {
	int res;

	assert(objList.isEmpty());
	assert(!objList.isFull());
	assert(objList.getCount()==0);

	res = objList.insert(new df::Object());
	assert(res == 0);

	assert(!objList.isEmpty());
	assert(!objList.isFull());
	assert(objList.getCount() == 1);

	res = objList.insert(new df::Object());
	assert(res == 0);

	res = objList.insert(new df::Object());
	assert(res == 0);

	df::Object obj;
	res = objList.insert(&obj);
	assert(res == 0);

	res = objList.insert(new df::Object());
	assert(res == 0);

	res = objList.insert(new df::Object());
	assert(res == 0);

	assert(!objList.isEmpty());
	assert(!objList.isFull());
	assert(objList.getCount() == 6);

	df::ObjectList objList2(objList);
	assert(objList.getCount() == objList2.getCount());
	assert(objList == objList2);

	res = objList.remove(&obj);
	assert(res == 0);

	assert(!objList.isEmpty());
	assert(!objList.isFull());
	assert(objList.getCount() == 5);

	assert(objList != objList2);

	df::ObjectList objListSum = objList2 + objList;
	assert(objListSum.getCount() == objList.getCount() + objList2.getCount());
	objList2 += objList;
	assert(objListSum == objList2);

	objList2 = objList;
	assert(objList == objList2);

	res = objList.remove(&obj);
	assert(res == -1);
	assert(!objList.isEmpty());
	assert(!objList.isFull());
	assert(objList.getCount() == 5);

	objList.clear();
	assert(objList.isEmpty());
	assert(!objList.isFull());
	assert(objList.getCount() == 0);

	df::Object* objs[df::MAX_OBJECTS];

	for (int i = 0; i < df::MAX_OBJECTS; i++) {
		objs[i] = new df::Object();
		res = objList.insert(objs[i]);
		assert(res == 0);
	}

	assert(!objList.isEmpty());
	assert(objList.isFull());
	assert(objList.getCount() == df::MAX_OBJECTS);

	res = objList.insert(new df::Object());
	assert(res == -1);

	assert(!objList.isEmpty());
	assert(objList.isFull());
	assert(objList.getCount() == df::MAX_OBJECTS);

	for (int i = 0; i < df::MAX_OBJECTS; i++) {
		res = objList.remove(objs[i]);
		assert(res == 0);
	}

	assert(objList.isEmpty());

	printf("Test Completed successfully");

	return 0;
}