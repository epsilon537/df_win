#include "Animation.h"

namespace df {
	Animation::Animation() : m_p_sprite(0), m_index(0), m_slowdown_count(0), m_box() {
	}

	//Set associated Sprite.
	//Note: Sprite is managed by ResourceManager.
	//Sprite index is set to 0.
	void Animation::setSprite(Sprite* p_new_sprite) {
		m_p_sprite = p_new_sprite;
		m_index = 0;

		if (m_p_sprite) {
			m_box = Box(Vector(0, 0), (float)m_p_sprite->getWidth(), (float)m_p_sprite->getHeight());
		}
		else {
			m_box = Box();
		}
	}

	//Return pointer to associated sprite.
	Sprite* Animation::getSprite() const {
		return m_p_sprite;
	}

	//Set index of current Sprite frame to be displayed.
	void Animation::setIndex(int new_index) {
		m_index = new_index;
	}

	//Get index of current Sprite frame to be displayed.
	int Animation::getIndex() const {
		return m_index;
	}

	//Set animation slowdown count (-1 means stop).
	void Animation::setSlowdownCount(int new_slowdown_count) {
		m_slowdown_count = new_slowdown_count;
	}

	//Get animation slowdown count (-1=stop)
	int Animation::getSlowdownCount() const {
		return m_slowdown_count;
	}

	//Draw single frame centered at given position.
	//Account for slowdown, and advance sprite frame.
	//Return 0 if ok, else -1.
	int Animation::draw(Vector position) {
		if (!m_p_sprite)
			return -1;

		//Draw current frame
		m_p_sprite->draw(m_index, position);

		//If slowdown count is -1, then animation is frozen
		if (m_slowdown_count == -1)
			return 0;

		//Increment counter
		int count = m_slowdown_count+1;
		//Advance sprite index if necessary.
		if (count >= m_p_sprite->getSlowdown()) {
			count = 0; //Reset counter

			int index = m_index+1;

			//If at last frame, loop to beginning.
			if (index >= m_p_sprite->getFrameCount())
				index = 0;

			m_index = index;
		}

		m_slowdown_count = count;
		return 0;
	}

	//Get Animation's bounding box
	Box Animation::getBox() const {
		return m_box;
	}
}