#include "DisplayManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include <stdio.h>
#include <assert.h>
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Object.h"

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

	std::string eType = p_e->getType();

	if (eType == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* ek = dynamic_cast<const df::EventKeyboard*>(p_e);
		int key = (int)ek->getKey();

		if (ek->getKeyboardAction() == df::KEY_PRESSED) {
			LM.writeLog("obj %d eventHandler received event: %s\n", getId(), eType.c_str());
			LM.writeLog("Key = %d\n", key);
			LM.writeLog("Key pressed\n");
		}
		else if (ek->getKeyboardAction() == df::KEY_RELEASED) {
			LM.writeLog("obj %d eventHandler received event: %s\n", getId(), eType.c_str());
			LM.writeLog("Key = %d\n", key);
			LM.writeLog("Key released\n");
		}
		else if (ek->getKeyboardAction() == df::KEY_DOWN) {
			//printf("obj %d eventHandler received event: %s\n", getId(), eType.c_str());
			//printf("Key down\n");
		}
		else {
			LM.writeLog("obj %d eventHandler received event: %s\n", getId(), eType.c_str());
			LM.writeLog("Key = %d\n", key);
			LM.writeLog("Unknown action\n");
		}
	}

	if (eType == df::MSE_EVENT) {
		const df::EventMouse* em = dynamic_cast<const df::EventMouse*>(p_e);

		if (em->getMouseAction() == df::CLICKED) {
			const char* button;

			if (em->getMouseButton() == df::Mouse::LEFT)
				button = "left";
			else if (em->getMouseButton() == df::Mouse::RIGHT)
				button = "right";
			else if (em->getMouseButton() == df::Mouse::MIDDLE)
				button = "middle";
			else
				button = "unknown";

			LM.writeLog("obj %d clicked event %s\n", getId(), eType.c_str());
			LM.writeLog("Button: %s\n", button);

			df::Vector v = em->getMousePosition();
			LM.writeLog("x=%f y=%f\n", v.getX(), v.getY());
		}
		else if (em->getMouseAction() == df::PRESSED) {
#if 0
			const char* button;

			if (em->getMouseButton() == df::Mouse::LEFT)
				button = "left";
			else if (em->getMouseButton() == df::Mouse::RIGHT)
				button = "right";
			else if (em->getMouseButton() == df::Mouse::MIDDLE)
				button = "middle";
			else
				button = "unknown";

			LM.writeLog("obj %d pressed event: %s\n", getId(), eType.c_str());
			LM.writeLog("Button: %s\n", button);

			df::Vector v = em->getMousePosition();
			LM.writeLog("x=%f y=%f\n", v.getX(), v.getY());
#endif
		}
		else if (em->getMouseAction() == df::MOVED) {
			const char* button;

			if (em->getMouseButton() == df::Mouse::LEFT)
				button = "left";
			else if (em->getMouseButton() == df::Mouse::RIGHT)
				button = "right";
			else if (em->getMouseButton() == df::Mouse::MIDDLE)
				button = "middle";
			else
				button = "unknown";

			LM.writeLog("obj %d moved event: %s\n", getId(), eType.c_str());
			LM.writeLog("Button: %s\n", button);

			df::Vector v = em->getMousePosition();
			LM.writeLog("x=%f y=%f\n", v.getX(), v.getY());
		}
		else {
			const char* button;

			if (em->getMouseButton() == df::Mouse::LEFT)
				button = "left";
			else if (em->getMouseButton() == df::Mouse::RIGHT)
				button = "right";
			else if (em->getMouseButton() == df::Mouse::MIDDLE)
				button = "middle";
			else
				button = "unknown";

			LM.writeLog("obj %d unknown mouse event\n", getId());
			LM.writeLog("Button: %s\n", button);

			df::Vector v = em->getMousePosition();
			LM.writeLog("x=%f y=%f\n", v.getX(), v.getY());
		}
	}

	return 1;
}

int main(void) {
	int res;
	TestObject obj1, obj2;

	LM.startUp();
	LM.setFlush();
	LM.setLogToScreen();

	res = IM.startUp();
	assert(res == -1);
	
	res = DM.startUp();
	assert(res == 0);

	res = IM.startUp();
	assert(res == 0);

	LM.writeLog("Test started\n");

	while (1) {
		IM.getInput();
	}

	IM.shutDown();
	DM.shutDown();

	printf("Test completed.\n");

	return 0;
}