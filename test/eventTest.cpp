#include "Event.h"
#include "EventStep.h"
#include "Object.h"
#include <stdio.h>
#include <assert.h>

class TestObject : public df::Object {
private:
public:
	TestObject();

	int eventHandler(const df::Event* p_e);
};

TestObject::TestObject() {
	setType("Test Object");
}

int TestObject::eventHandler(const df::Event* p_e) {
	assert(p_e);

	printf("eventHandler received event: %s\n", p_e->getType().c_str());
	return 1;
}

int main(void) {
	df::Event event;

	printf("Default event type: %s\n", event.getType().c_str());

	event.setType("Test Type");

	printf("Event type after set: %s\n", event.getType().c_str());

	df::EventStep eventStep;

	printf("eventStep type: %s\n", eventStep.getType().c_str());
	assert(eventStep.getStepCount() == 0);

	eventStep.setStepCount(10);
	
	assert(eventStep.getStepCount() == 10);

	df::EventStep eventStep2(20);
	assert(eventStep2.getStepCount() == 20);
	printf("eventStep2 type: %s\n", eventStep2.getType().c_str());

	TestObject testObject;

	printf("testObject type:%s\n", testObject.getType().c_str());

	testObject.eventHandler(&event);

	testObject.eventHandler(&eventStep);

	return 0;
}