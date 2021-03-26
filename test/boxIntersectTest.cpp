#include "utility.h"
#include "EventKeyboard.h"
#include "EventStep.h"
#include "GameManager.h"
#include "Object.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "InputManager.h"
#include <assert.h>

class TestObject;

TestObject* obj1p = 0;
TestObject* obj2p = 0;

class TestObject : public df::Object {
private:
	df::Color m_color;
	char m_c;
	bool m_focus;

public:
	TestObject(df::Color color, char c, bool f) : m_color(color), m_c(c), m_focus(f) {
		registerInterest(df::STEP_EVENT);
		registerInterest(df::KEYBOARD_EVENT);
	}

	~TestObject() {}

	int draw() {
		for (int x = 0; x < getBox().getHorizontal(); x++) {
			for (int y = 0; y < getBox().getVertical(); y++) {
				DM.drawCh(getBox().getCorner() + df::Vector((float)x, (float)y), m_c, m_color);
			}
		}

		return 0;
	}

	int eventHandler(const df::Event* p_e) {
		assert(p_e);

		std::string eType = p_e->getType();

		if (eType == df::STEP_EVENT) {
			if (obj1p && obj2p) {
				if (df::boxIntersectBox(obj1p->getBox(), obj2p->getBox())) {
					LM.writeLog("X");
				}
				else {
					LM.writeLog("O");
				}
			}
		}

		if (eType == df::KEYBOARD_EVENT) {
			const df::EventKeyboard* ek = dynamic_cast<const df::EventKeyboard*>(p_e);
			int key = (int)ek->getKey();
			df::Box box;

			if (ek->getKeyboardAction() == df::KEY_PRESSED) {

				if (key == df::Keyboard::F) {
					m_focus = !m_focus;
				}

				if (!m_focus)
					return 0;

				switch (key) {
				case df::Keyboard::LEFTARROW:
					box = getBox();
					box.setCorner(box.getCorner() + df::Vector(-1, 0));
					setBox(box);
					break;
				case df::Keyboard::RIGHTARROW:
					box = getBox();
					box.setCorner(box.getCorner() + df::Vector(1, 0));
					setBox(box);
					break;
				case df::Keyboard::UPARROW:
					box = getBox();
					box.setCorner(box.getCorner() + df::Vector(0, -1));
					setBox(box);
					break;
				case df::Keyboard::DOWNARROW:
					box = getBox();
					box.setCorner(box.getCorner() + df::Vector(0, 1));
					setBox(box);
					break;
				case df::Keyboard::PLUS:
					box = getBox();
					box.setHorizontal(box.getHorizontal() + 1);
					setBox(box);
					break;
				case df::Keyboard::MINUS:
					box = getBox();
					box.setHorizontal(box.getHorizontal() - 1);
					setBox(box);
					break;
				case df::Keyboard::SLASH:
					box = getBox();
					box.setVertical(box.getVertical() - 1);
					setBox(box);
					break;
				case df::Keyboard::COMMA:
					box = getBox();
					box.setVertical(box.getVertical() + 1);
					setBox(box);
					break;
				}
			}
		}

		return 0;
	}
};

int main(void) {
	GM.startUp();

	LM.setLogToScreen();

	TestObject obj1(df::YELLOW,'*', false);
	TestObject obj2(df::BLUE, 'X', true);
	
	obj1p = &obj1;
	obj2p = &obj2;

	//obj1.setPosition(df::Vector((float)DM.getHorizontal() * 0.25f, (float)DM.getVertical() * 0.25f));
	//obj2.setPosition(df::Vector((float)DM.getHorizontal() * 0.25f, (float)DM.getVertical() * 0.25f));

	GM.run();
	GM.shutDown();

	return 0;
}