#include "ViewObject.h"
#include <assert.h>
#include <stdio.h>
#include "GameManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include <Windows.h>

int main(void) {
	//int res;

	GM.startUp();
	LM.setLogToScreen();

	df::Box world = WM.getBoundary();
	world.setHorizontal(world.getHorizontal() * 2);
	world.setVertical(world.getVertical() * 2);
	WM.setBoundary(world);

	df::Box view = WM.getView();
	view.setCorner(view.getCorner() + df::Vector(view.getHorizontal() * 0.5f, 0));
	WM.setView(view);

	df::ViewObject *vo1 = new df::ViewObject();
	vo1->setViewString("Hello World");
	//res = vo->draw();
	//assert(res == 0);

	df::ViewObject* vo2 = new df::ViewObject();
	vo2->setViewString("Hello World");
	vo2->setLocation(df::CENTER_CENTER);
	vo2->setBorder(false);
	//res = vo->draw();
	//assert(res == 0);

	df::ViewObject* vo3 = new df::ViewObject();
	vo3->setViewString("Hello World");
	vo3->setLocation(df::BOTTOM_LEFT);
	vo3->setBorder(true);
	//res = vo->draw();
	//assert(res == 0);

	df::ViewObject* vo4 = new df::ViewObject();
	vo4->setViewString("Hello World");
	vo4->setLocation(df::BOTTOM_RIGHT);
	vo4->setBorder(true);
	vo4->setColor(df::YELLOW);
	//res = vo->draw();
	//assert(res == 0);

	df::ViewObject* vo5 = new df::ViewObject();
	vo5->setViewString("Hello World");
	vo5->setLocation(df::TOP_LEFT);
	vo5->setBorder(true);
	vo5->setColor(df::YELLOW);
	vo5->setDrawValue(false);
	//res = vo->draw();
	//assert(res == 0);

	df::ViewObject* vo6 = new df::ViewObject();
	vo6->setViewString("Hello World");
	vo6->setLocation(df::CENTER_RIGHT);
	vo6->setBorder(true);
	vo6->setColor(df::YELLOW);
	vo6->setDrawValue(true);
	vo6->setValue(12345678);

	assert(vo6->getViewString() == "Hello World");
	assert(vo6->getLocation() == df::CENTER_RIGHT);
	assert(vo6->getBorder() == true);
	assert(vo6->getColor() == df::YELLOW);
	assert(vo6->getDrawValue() == true);
	assert(vo6->getValue() == 12345678);

	//res = vo->draw();
	//assert(res == 0);

	//DM.swapBuffers();
	GM.run();

	//Sleep(10000);

	GM.shutDown();
	return 0;
}