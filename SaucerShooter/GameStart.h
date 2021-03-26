#include "ViewObject.h"
#include "Object.h"
#include "Music.h"

class GameStart : public df::ViewObject {
private:
	df::Music* p_music;

public:
	GameStart();
	int eventHandler(const df::Event* p_e);
	int draw(void);
	void playMusic();
	void start();
};
