#include "ViewObject.h"

class GameOver : public df::ViewObject {
private:
	int time_to_live;
	void step();

public:
	GameOver();
	virtual ~GameOver();


	int draw(void);
	int eventHandler(const df::Event* p_e);
};
