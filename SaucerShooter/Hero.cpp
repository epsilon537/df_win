#include "Hero.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventStep.h"
#include "GameManager.h"
#include "Bullet.h"
#include "EventNuke.h"
#include "EventView.h"
#include "GameOver.h"
#include "Sound.h"
#include "DisplayManager.h"
#include <assert.h>

Hero::Hero() {
	// Link to "ship" sprite.
	setSprite("ship");
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);

	setType("Hero");
	df::Vector p(7, WM.getView().getCorner().getY() + WM.getView().getVertical() / 2);
	setPosition(p);

	//int res = WM.setViewFollowing(this);
	//assert(res==0);

	move_slowdown = 2;
	move_countdown = move_slowdown;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;

	nuke_count = 1;

	p_reticle = new Reticle();
	p_reticle->draw();
}

int Hero::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	else if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	else if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast<const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}

	return 0;
}

void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::Q:	//quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.markForDelete(this);
		break;
	case df::Keyboard::W:	// up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(-1);
		break;
	case df::Keyboard::S:	// down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(+1);
		break;
	case df::Keyboard::SPACE: // nuke
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			nuke();
	}
}

// Move up or down
void Hero::move(int dy) {
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// If stays on window, allow move
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
	if ((new_pos.getY() > 3) &&
		(new_pos.getY() < WM.getBoundary().getVertical() - 1))
		WM.moveObject(this, new_pos);

	//Adjust view
	//WM.setViewPosition(new_pos);
	//df::Box new_view = WM.getView();
	//df::Vector corner = new_view.getCorner();
	//corner.setY(corner.getY() + dy);
	//new_view.setCorner(corner);
	//WM.setView(new_view);
}

// Decrease rate restriction counters.
void Hero::step() {
	// Move countdown
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;

	// Fire countdown
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}

void Hero::fire(df::Vector target) {
	if (fire_countdown > 0)
		return;

	fire_countdown = fire_slowdown;

	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Bullet* p = new Bullet(getPosition());
	p->setVelocity(v);

	//Play "fire" sound.
	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play();
}

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse* p_mouse_event) {
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
		fire(p_mouse_event->getMousePosition());
}

void Hero::nuke() {
	// Check if nukes left
	if (!nuke_count)
		return;

	nuke_count--;

	// Create "nuke: event and send to interested Objects.
	EventNuke nuke;
	WM.onEvent(&nuke);

	//Send "view" event with nukes to interested viewObjects.
	df::EventView ev("Nukes", -1, true);
	WM.onEvent(&ev);

	// Shake screen (severity 15 pixels x&y, duration 5 frames).
	//DM.shake(15, 15, 5);

	//Play "nuke" sound
	df::Sound* p_sound = RM.getSound("nuke");
	p_sound->play();
}

Hero::~Hero() {
	// Create GameOver object.
	new GameOver;

	// Mark Reticle for deletion.
	WM.markForDelete(p_reticle);

	// Make a big explosion with particles.
	//df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	//df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
	//df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	//df::addParticles(df::SPARKS, getPosition(), 3, df::RED);

	// Shake screen (severity 20 pixels x&y, duration 10 frames).
	//DM.shake(20, 20, 10);
}