#include "utility.h"
#include "EventKeyboard.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "GameManager.h"
#include "Object.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "WorldManager.h"
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
		registerInterest(df::COLLISION_EVENT);
	}

	~TestObject() {}

	int draw() {
		Object::draw();

		df::Vector b(getWorldBox(this).getCorner());
		DM.drawCh(b, 'b', df::GREEN);

		df::Vector B(getWorldBox(this).getCorner() + df::Vector(getBox().getHorizontal(), getBox().getVertical()));
		DM.drawCh(B, 'B', df::GREEN);

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
			df::Vector center((float)DM.getHorizontal() * 0.5f, (float)DM.getVertical() * 0.5f);

			DM.drawCh(center, '+', df::WHITE);

			if (boxContainsPosition(getWorldBox(this), center)) {
				LM.writeLog("!");
			}

			assert(obj1p);
			assert(obj2p);

			if (boxContainsBox(getWorldBox(obj1p), getWorldBox(obj2p))) {
				LM.writeLog("?");
			}

			if (boxContainsBox(getWorldBox(obj2p), getWorldBox(obj1p))) {
				LM.writeLog(".");
			}
		}

		
		if (eType == df::COLLISION_EVENT) {
			LM.writeLog("X");
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
				case df::Keyboard::T:
					if (this == obj1p)
						obj2p->setActive(!obj2p->isActive());
					else
						obj1p->setActive(!obj1p->isActive());
					break;
				case df::Keyboard::X:
					setSolidness(df::SPECTRAL);
					break;
				case df::Keyboard::H:
					setSolidness(df::HARD);
					break;
				case df::Keyboard::W:
					setVelocity(getVelocity() + df::Vector(0, -0.1f));
					break;
				case df::Keyboard::A:
					setVelocity(getVelocity() + df::Vector(-0.1f, 0));
					break;
				case df::Keyboard::S:
					setVelocity(getVelocity() + df::Vector(0, 0.1f));
					break;
				case df::Keyboard::D:
					setVelocity(getVelocity() + df::Vector(0.1f, 0));
					break;
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

	df::Vector v1(2, 4);
	df::Vector v2(4, 5);
	LM.writeLog("dist(v1,v2)=%f\n", distance(v1, v2));

	TestObject obj1(df::YELLOW, '*', false);
	TestObject obj2(df::BLUE, 'X', true);

	int res = RM.loadSprite("sprites/orig.txt", "Saucer");
	assert(res == 0);

	res = RM.loadSprite("sprites/ship-spr.txt", "Ship");
	assert(res == 0);

	obj1.setSprite("Saucer");
	obj2.setSprite("Ship");
	obj1.setSolidness(df::SOFT);
	obj2.setSolidness(df::SOFT);

	obj1p = &obj1;
	obj2p = &obj2;

	obj1.setPosition(df::Vector((float)DM.getHorizontal() * 0.25f, (float)DM.getVertical() * 0.25f));
	obj2.setPosition(df::Vector((float)DM.getHorizontal() * 0.75f, (float)DM.getVertical() * 0.75f));

	GM.run();
	GM.shutDown();

	return 0;
}