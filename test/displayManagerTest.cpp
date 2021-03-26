#include "DisplayManager.h"
#include "LogManager.h"
#include "Vector.h"
#include <assert.h>
#include <Windows.h>

int main(void) {
	LM.startUp();

	int res = DM.startUp();
	assert(res == 0);

	sf::RenderWindow* window = DM.getWindow();
	assert(window);

	LM.writeLog("char width: %f\n", df::charWidth());
	LM.writeLog("char Height: %f\n", df::charHeight());

	// Return window's horizontal max. (in characters).
	LM.writeLog("Horizontal = %d\n", DM.getHorizontal());

	// Return window's vertical max. (in character).
	LM.writeLog("Vertical = %d\n", DM.getVertical());

	// Return window's horizontal max (in pixels).
	LM.writeLog("Horizontal pixels = %d\n", DM.getHorizontalPixels());

	// Return window's vertical max (in pixels).
	LM.writeLog("Vertical pixels = %d\n", DM.getVerticalPixels());

	res = DM.drawString(df::Vector((float)(DM.getHorizontal())/2, (float)(DM.getVertical())/2), "Hello World", df::CENTER_JUSTIFIED, df::YELLOW);
	assert(res == 0);

	res = DM.swapBuffers();
	assert(res == 0);

	Sleep(5000);

	DM.shutDown();
	LM.shutDown();

	return 0;
}