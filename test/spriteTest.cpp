#include "Sprite.h"
#include "Frame.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "GameManager.h"
#include "Color.h"
#include <Windows.h>
#include <assert.h>

int main(void) {
	int res;

	GM.startUp();

	LM.setLogToScreen();

	df::Sprite sprite(3);

	sprite.setWidth(4);
	sprite.setHeight(2);
	sprite.setColor(df::YELLOW);
	sprite.setLabel("Test");
	sprite.setSlowdown(2);

	df::Frame frame;
	frame.setHeight(2);
	frame.setWidth(4);
	frame.setString("12344321");
	res = sprite.addFrame(frame);
	assert(res == 0);

	frame.setString("56788765");
	res = sprite.addFrame(frame);
	assert(res == 0);

	assert(sprite.getWidth() == 4);
	assert(sprite.getHeight() == 2);
	assert(sprite.getColor() == df::YELLOW);
	assert(sprite.getLabel() == "Test");
	assert(sprite.getSlowdown() == 2);
	assert(sprite.getFrameCount() == 2);

	df::Frame frame2 = sprite.getFrame(1);

	assert(frame2.getHeight() == frame.getHeight());
	assert(frame2.getWidth() == frame.getWidth());
	assert(frame2.getString() == frame.getString());

	frame2 = sprite.getFrame(5);

	df::Frame emptyFrame;

	assert(frame2.getHeight() == emptyFrame.getHeight());
	assert(frame2.getWidth() == emptyFrame.getWidth());
	assert(frame2.getString() == emptyFrame.getString());

	frame.setString("abcddcba");
	res = sprite.addFrame(frame);
	assert(res == 0);

	frame.setString("ABCDDCBA");
	res = sprite.addFrame(frame);
	assert(res == -1);

	int ii = 0;

	while (1) {
		sprite.draw(ii++, df::Vector((float)DM.getHorizontal() / 2, (float)DM.getVertical() / 2));
		
		if (ii >= sprite.getFrameCount())
			ii = 0;

		DM.swapBuffers();
		Sleep(500); //Sleep is in ms.
	}

	LM.writeLog("Test completed.\n");
	GM.shutDown();
	return 0;
}