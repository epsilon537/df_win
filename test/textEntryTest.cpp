#include "TextEntry.h"
#include "GameManager.h"
#include "LogManager.h"
#include <stdio.h>
#include <assert.h>

class TextEntryTest : public df::TextEntry {
public:
	virtual void callback() {
		LM.writeLog("Enter pressed\n");

		assert(getPrefix() == "");
		assert(getText().size() == 16);
		assert(getPrefix() == "");
		assert(getLimit() == 16);
		//assert(textEntryp->getCursor() == 0);
		//assert(textEntryp->getBlinkRate() == df::TEXT_ENTRY_DEFAULT_BLINK_RATE);
		assert(numbersOnly() == false);
		assert(getCursorChar() == '_');

		setBlinkRate(5);
		setPrefix("Prefix: ");
		setNumbersOnly();
		setLimit(4);
		setCursorChar('*');
	}

	virtual ~TextEntryTest() {
	}
};

int main(void) {
	GM.startUp();
	LM.setLogToScreen();

	TextEntryTest* textEntryp = new TextEntryTest();

	//Check defaults
	assert(textEntryp->getPrefix() == "");
	assert(textEntryp->getText() == "");
	assert(textEntryp->getPrefix() == "");
	assert(textEntryp->getLimit() == 0);
	assert(textEntryp->getCursor() == 0);
	assert(textEntryp->getBlinkRate() == df::TEXT_ENTRY_DEFAULT_BLINK_RATE);
	assert(textEntryp->numbersOnly() == false);
	assert(textEntryp->getCursorChar() == '_');

	textEntryp->setLocation(df::CENTER_CENTER);
	textEntryp->setBorder(true);
	textEntryp->setColor(df::YELLOW);
	textEntryp->setDrawValue(false);
	textEntryp->setLimit(16);

	GM.run();

	GM.shutDown();
	printf("Test Done.\n");
	return 0;
}