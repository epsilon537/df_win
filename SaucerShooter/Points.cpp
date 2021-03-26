#include "Points.h"
#include "GameManager.h"
#include "EventStep.h"

Points::Points() {
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);

	registerInterest(df::STEP_EVENT);
}

int Points::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		if (dynamic_cast<const df::EventStep*>(p_e)->getStepCount() % 30 == 0)
			setValue(getValue() + 1);
		return 1;
	}
	else {
		/*Defer to parent*/
		return ViewObject::eventHandler(p_e);
	}

	return 0;
}
