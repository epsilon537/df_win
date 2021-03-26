#include "Saucer.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "Explosion.h"
#include "EventNuke.h"
#include "Points.h"
#include "EventView.h"
#include "Sound.h"
#include <stdlib.h>

Saucer::Saucer() {
	registerInterest(NUKE_EVENT);

	// Set up "saucer" sprite.
	setSprite("saucer");

	// Set object type.
	setType("Saucer");

	// Set speed in horizontal direction.
	setVelocity(df::Vector(-0.25, 0)); // 1 space left every 4 frames

	moveToStart();
}

int Saucer::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	else if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	else if (p_e->getType() == NUKE_EVENT) {
		nuke();
		return 1;
	}

	return 0;
}

void Saucer::out() {
	if (getPosition().getX() >= 0)
		return;

	moveToStart();

	// Spawn new Saucer to make the game get harder.
	new Saucer;
}

void Saucer::moveToStart() {
	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// x is off right side of window
	temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);
	temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);

	// If collision, move right slightly until empty space.
	df::ObjectList collistion_list = WM.getCollisions(this, temp_pos);
	while (!collistion_list.isEmpty()) {
		temp_pos.setX(temp_pos.getX() + 1);
		collistion_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}

void Saucer::hit(const df::EventCollision* p_c) {
	if ((p_c->getObject1()->getType() == "Saucer") &&
		(p_c->getObject2()->getType() == "Saucer"))
		return;

	if ((p_c->getObject1()->getType() == "Bullet") ||
		(p_c->getObject2()->getType() == "Bullet")) {
		// Create an explosion.
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		// Saucers stay around perpetually.
		new Saucer;
	}

	if ((p_c->getObject1()->getType() == "Hero") ||
		(p_c->getObject2()->getType() == "Hero")) {
		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());
	}

	//Play "explode" sound.
	df::Sound* p_sound = RM.getSound("explode");
	p_sound->play();
}

void Saucer::nuke() {
	// Create an explosion.
	Explosion* p_explosion = new Explosion;
	p_explosion->setPosition(this->getPosition());

	//Mark self for deletion.
	WM.markForDelete(this);

	// Saucers stay around perpetually.
	new Saucer;
}

Saucer::~Saucer() {
	// Send "view" event with points to interested ViewObjects.
	// Add 10 points.
	df::EventView ev(POINTS_STRING, 10, true);
	WM.onEvent(&ev);
}