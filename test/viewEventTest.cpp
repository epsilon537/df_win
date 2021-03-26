#include "GameManager.h"
#include "LogManager.h"
#include "ViewObject.h"
#include "EventView.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include <Windows.h>
#include <stdio.h>
#include <assert.h>

df::ViewObject* vo=0;

class TestObject : public df::Object {
private:
public:
	TestObject() {
		registerInterest(df::STEP_EVENT);
	}

	virtual int draw() {
		return 0;
	}

	int eventHandler(const df::Event* p_e) {
		assert(p_e);

		//See if this is a step event.
		if (p_e->getType() == df::STEP_EVENT) {
			int frameCount = GM.getFrameCount();

			if (frameCount == 100) {

				df::EventView ev("Points", 10, true);
				assert(ev.getTag() == "Points");
				assert(ev.getValue() == 10);
				assert(ev.getDelta() == true);

				WM.onEvent(&ev);
			}

			if (frameCount == 200) {

				df::EventView ev("Points", 10, true);
				assert(ev.getTag() == "Points");
				assert(ev.getValue() == 10);
				assert(ev.getDelta() == true);

				WM.onEvent(&ev);
			}

			if (frameCount == 300) {

				df::EventView ev("Points", 10, true);
				ev.setDelta(false);
				ev.setValue(1000);
				assert(ev.getDelta() == false);
				assert(ev.getValue() == 1000);
				assert(ev.getTag() == "Points");

				WM.onEvent(&ev);
			}

			if (frameCount == 400) {
				assert(vo);
				vo->setViewString("ValMustNotChg");
			}

			if (frameCount == 500) {
				df::EventView ev("Points", 10, true);
				ev.setDelta(false);
				ev.setValue(1000);
				ev.setTag("Something else");
				assert(ev.getTag() == "Something else");
				WM.onEvent(&ev);
			}
		}

		return 0;
	}
};

int main(void) {
	GM.startUp();
	LM.setLogToScreen();

	TestObject *obj = new TestObject();

	vo = new df::ViewObject();
	vo->setViewString("Points");
	
	GM.run();

	GM.shutDown();
	printf("Test done.\n");
	return 0;
}