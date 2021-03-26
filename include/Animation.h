#ifndef __DF_ANIMATION_H__
#define __DF_ANIMATION_H__

#include <string>
#include "Sprite.h"
#include "Vector.h"
#include "Box.h"

namespace df {
	class Animation {
	private:
		Sprite* m_p_sprite; //Sprite associated with Animation.
		int m_index; //Current index frame for Sprite.
		int m_slowdown_count; //Slowdown counter.
		Box m_box;

	public:
		Animation();

		//Set associated Sprite.
		//Note: Sprite is managed by ResourceManager.
		//Sprite index is set to 0.
		void setSprite(Sprite* p_new_sprite);

		//Return pointer to associated sprite.
		Sprite* getSprite() const;

		//Set index of current Sprite frame to be displayed.
		void setIndex(int new_index);

		//Get index of current Sprite frame to be displayed.
		int getIndex() const;

		//Set animation slowdown count (-1 means stop).
		void setSlowdownCount(int new_slowdown_count);

		//Get animation slowdown count (-1=stop)
		int getSlowdownCount() const;

		//Draw single frame centered at given position.
		//Account for slowdown, and advance sprite frame.
		//Return 0 if ok, else -1.
		int draw(Vector position);

		//Get Animation's bounding box
		Box getBox() const;
	};
}

#endif /*DF_ANIMATION*/
