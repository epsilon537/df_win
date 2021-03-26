#include "Frame.h"
#include "DisplayManager.h"
#include "Vector.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
	DM.startUp();

	df::Frame frame;

	assert(frame.getHeight() == 0);
	assert(frame.getWidth() == 0);
	assert(frame.getString().empty());

	frame.setHeight(3);
	frame.setWidth(2);
	frame.setString("121212");

	assert(frame.getHeight() == 3);
	assert(frame.getWidth() == 2);
	assert(frame.getString() == "121212");

	frame.draw(df::Vector((float)DM.getHorizontal() / 2, (float)DM.getVertical() / 2), df::BLUE);

	frame.setHeight(5);
	frame.setWidth(5);
	frame.setString("1234567890abcdeABCDE54321");
	frame.draw(df::Vector((float)DM.getHorizontal() *0.25f, (float)DM.getVertical() / 2), df::YELLOW);

	DM.swapBuffers();

	printf("Test Complete.\n");

	while (1);

	DM.shutDown();

	return 0;
}