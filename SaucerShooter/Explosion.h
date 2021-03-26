#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "Object.h"

class Explosion : public df::Object {
private:
	int time_to_live;
	void step();

public:
	Explosion();
	int eventHandler(const df::Event* p_e);
};

#endif /*__EXPLOSION_H__*/