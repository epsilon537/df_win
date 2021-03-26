#include "GameStart.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "ResourceManager.h"
#include "Saucer.h"
#include "Hero.h"
#include "Points.h"
#include "Color.h"

GameStart::GameStart() {
	// Set object type.
	setType("GameStart");

	setSprite("gamestart");

	// Put in center of window
	setLocation(df::CENTER_CENTER);

	// Register for keyboard events.
	registerInterest(df::KEYBOARD_EVENT);

	// Play start music
	p_music = RM.getMusic("start music");
	playMusic();
}

int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		switch (p_keyboard_event->getKey()) {
			case df::Keyboard::P:	// play
				start();
				break;
			case df::Keyboard::Q:	// quit
				GM.setGameOver();
				break;
			default:	// Key is not handled.
				break;
		}
	}

	// If we get here, ignore the event.
	return 0;
}

void GameStart::start() {
	new Hero;

	for (int i = 0; i < 16; i++) {
		new Saucer;
	}

	// Setup heads-up display.
	new Points; // points display

	df::ViewObject* p_vo = new df::ViewObject; // Count of nukes.

	p_vo->setLocation(df::TOP_LEFT);
	p_vo->setViewString("Nukes");
	p_vo->setValue(1);
	p_vo->setColor(df::YELLOW);

	// Pause start music.
	p_music->pause();

	// When game syatys, become inactive.
	setActive(false);
}

int GameStart::draw(void) {
	return df::Object::draw();
}

void GameStart::playMusic() {
	p_music->play();
}
