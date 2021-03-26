#include "Star.h"
#include <stdlib.h>
#include "WorldManager.h"
#include "DisplayManager.h"
#include "EventOut.h"
//#include "Shape.h"
#include "Color.h"

Star::Star() {
	setType("Star");
	setSolidness(df::SPECTRAL);

	setVelocity(df::Vector((float)-1.0 /(rand() % 10 + 1), 0));
	setAltitude(0);  // Make Stars in background.

	df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
				 (float)(rand() % (int)WM.getBoundary().getVertical()));
	setPosition(p);

	// Draw Start with circle.
	// Close starts are bigger and move faster.
	//df::Shape s;
	//s.setColor(df::WHITE);
	//s.setType(df::CIRCLE);
	//s.setSize(5 * getVelocity().getMagnitude());
	//setShape(s);
}

int Star::draw() {
	return DM.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}

int Star::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	return 0;
}

void Star::out() {
	df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal() + rand()%20),
		(float)(rand() % (int)WM.getBoundary().getVertical()));
	setPosition(p);
	setVelocity(df::Vector((float)-1.0 / (rand() % 10 + 1), 0));

	// Draw Start with circle.
	// Close starts are bigger and move faster.
	//df::Shape s;
	//s.setColor(df::WHITE);
	//s.setType(df::CIRCLE);
	//s.setSize(5 * getVelocity().getMagnitude());
	//setShape(s);
}