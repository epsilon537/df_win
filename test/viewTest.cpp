#include "utility.h"
#include "EventKeyboard.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "GameManager.h"
#include "Object.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include <assert.h>

int main(void) {
	df::Box world = WM.getBoundary();
	assert(world == df::Box());
	df::Box view = WM.getView();
	assert(view == df::Box());

	GM.startUp();

	world = WM.getBoundary();
	assert(world == df::Box(df::Vector(0,0), (float)DM.getHorizontal(), (float)DM.getVertical()));
	view = WM.getView();
	assert(world == df::Box(df::Vector(0, 0), (float)DM.getHorizontal(), (float)DM.getVertical()));

	LM.setLogToScreen();

	world.setCorner(df::Vector(-100, -200));
	world.setHorizontal(200);
	world.setVertical(400);
	WM.setBoundary(world);
	assert(WM.getBoundary() == world);

	view.setCorner(df::Vector(-50, -20));
	view.setHorizontal(100);
	view.setVertical(40);
	WM.setView(view);
	assert(WM.getView() == view);

	df::Vector vw = df::Vector(-30, -10);
	df::Vector vv = worldToView(vw);
	assert(vv == df::Vector(20, 10));

	LM.writeLog("Test Complete\n");

	GM.shutDown();

	return 0;
}