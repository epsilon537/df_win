#include "ObjectListIterator.h"
#include "ObjectList.h"
#include <assert.h>
#include <stdio.h>

df::ObjectList objectList, objectList2;

int main(void) {
	df::Object obj1, obj2;

	objectList.insert(&obj1);
	objectList.insert(&obj2);
	objectList.insert(new df::Object);
	objectList.insert(new df::Object);
	objectList.insert(new df::Object);

	assert(objectList.getCount() == 5);

	df::ObjectListIterator iter(&objectList);
	df::ObjectListIterator iter2(&objectList2);

	assert(iter.currentObject() == &obj1);

	iter.next();

	assert(iter.currentObject() == &obj2);

	iter.first();

	assert(iter.currentObject() == &obj1);

	assert(!iter.isDone());

	iter.next();

	assert(!iter.isDone());

	iter.next();
	assert(!iter.isDone());

	iter.next();
	assert(!iter.isDone());

	iter.next();
	assert(!iter.isDone());

	iter.next();
	assert(iter.isDone());

	printf("First Pass:\n");
	for (iter.first(); !iter.isDone(); iter.next()) {
		printf("obj id: %d\n", iter.currentObject()->getId());
	}

	printf("Second Pass:\n");
	for (iter.first(); !iter.isDone(); iter.next()) {
		printf("obj id: %d\n", iter.currentObject()->getId());
	}

	objectList2 = objectList;
	printf("ObjectList2 should be equal objectList1:\n");
	for (iter.first(); !iter.isDone(); iter.next()) {
		printf("obj id: %d\n", iter.currentObject()->getId());
	}
	for (iter2.first(); !iter2.isDone(); iter2.next()) {
		printf("obj id: %d\n", iter2.currentObject()->getId());
	}

	objectList2 += objectList;
	printf("ObjectList2 should contain itself and objectList:\n");
	for (iter2.first(); !iter2.isDone(); iter2.next()) {
		printf("obj id: %d\n", iter2.currentObject()->getId());
	}

	df::ObjectList objectList3 = objectList2 + objectList;
	df::ObjectListIterator iter3(&objectList3);
	printf("ObjectList3 should contain objectList2 and objectList:\n");
	for (iter3.first(); !iter3.isDone(); iter3.next()) {
		printf("obj id: %d\n", iter3.currentObject()->getId());
	}

	printf("Halfway removing object:\n");
	int ii = 0;
	for (iter.first(); !iter.isDone(); iter.next()) {
		if (ii == 2)
			objectList.remove(&obj1);
		printf("obj id: %d\n", iter.currentObject()->getId());
		++ii;
	}

	printf("Halfway inserting object:\n");
	ii = 0;
	for (iter.first(); !iter.isDone(); iter.next()) {
		if (ii == 2)
			objectList.insert(&obj1);
		printf("obj id: %d\n", iter.currentObject()->getId());
		++ii;
	}

	printf("Halway clearing list:\n");
	ii = 0;
	for (iter.first(); !iter.isDone(); iter.next()) {
		if (ii == 2)
			objectList.clear();
		df::Object *objp = iter.currentObject();

		if (objp)
			printf("obj id: %d\n", objp->getId());
		else
			printf("ii=%d, objp=0\n", ii);

		++ii;
	}

	printf("Empty list loop:\n");
	for (iter.first(); !iter.isDone(); iter.next()) {
		if (ii == 2)
			objectList.insert(&obj1);
		printf("obj id: %d\n", iter.currentObject()->getId());
		++ii;
	}

	printf("Test Completed successfully\n");

	return 0;
}