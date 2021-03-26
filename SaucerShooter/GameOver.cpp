#include "GameOver.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "Sound.h"
#include "ResourceManager.h"
#include "GameStart.h"
#include "ObjectListIterator.h"

GameOver::GameOver() {
	// Set object type.
	setType("GameOver");

	if (setSprite("gameover") == 0)
		// Set live time as long as sprite length.
		time_to_live = getAnimation().getSprite()->getFrameCount() *
			getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;

	// Put in center of window
	setLocation(df::CENTER_CENTER);

	// Register for step event.
	registerInterest(df::STEP_EVENT);

	// Play "game over" sound.
	df::Sound* p_sound = RM.getSound("game over");
	p_sound->play();
}

int GameOver::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

GameOver::~GameOver() {
	// Remove Saucers and ViewObjects, re-activate GameStart.
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if ((p_o->getType() == "Saucer") || (p_o->getType() == "ViewObject"))
			WM.markForDelete(p_o);
		if (p_o->getType() == "GameStart") {
			p_o->setActive(true);
			dynamic_cast<GameStart*>(p_o)->playMusic(); // Resume start music.
		}
	}
}

int GameOver::draw(void) {
	return df::Object::draw();
}