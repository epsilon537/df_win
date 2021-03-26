#include "Reticle.h"
#include "EventMouse.h"
#include "DisplayManager.h"
#include "WorldManager.h"

Reticle::Reticle() {
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();

	df::Vector p((float)world_horiz/2, (float)world_vert/2);
	setPosition(p);

	setType("Reticle");
	setSolidness(df::SPECTRAL);
	setAltitude(df::MAX_ALTITUDE); // Make Reticle in foreground.

	registerInterest(df::MSE_EVENT);
}

int Reticle::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast<const df::EventMouse*> (p_e);
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			// Change location to new mouse position.
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}
	}

	return 0;
}

// Draw reticle on window.
int Reticle::draw() {
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}