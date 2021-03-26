#include "EventKeyboard.h"
#include "EventMouse.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
	df::EventKeyboard ek;

	for (int k = (int)(df::KEY_PRESSED); k <= (int)(df::KEY_DOWN); k++) {
		ek.setKeyboardAction((df::EventKeyboardAction)k);
		assert(k == (int)ek.getKeyboardAction());
	}

	for (int k = (int)(df::Keyboard::SPACE); k <= (int)(df::Keyboard::NUM0); k++) {
		ek.setKey((df::Keyboard::Key)k);
		assert(k == (int)ek.getKey());
	}

	df::EventMouse em;

	for (int m = (int)(df::Mouse::LEFT); m <= (int)(df::Mouse::MIDDLE); m++) {
		em.setMouseButton((df::Mouse::Button)m);
		assert(m == (int)em.getMouseButton());
	}

	for (int m = (int)(df::CLICKED); m <= (int)(df::MOVED); m++) {
		em.setMouseAction((df::EventMouseAction)m);
		assert(m == (int)em.getMouseAction());
	}

	em.setMousePosition(df::Vector(10,20));
	assert(df::Vector(10,20) == em.getMousePosition());

	printf("Test complete.\n");

	return 0;
}