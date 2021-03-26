#include "Sprite.h"
#include "LogManager.h"
#include "Frame.h"

#include <new>

namespace df {
	//Destroy sprite, deleting any allocated frames.
	Sprite::~Sprite() {
		if (m_frame)
			delete[] m_frame;
	}

	//Create sprite with indicated max. number of frames.
	Sprite::Sprite(int max_frames) : m_width(0), m_height(0), m_max_frame_count(max_frames),
		m_frame_count(0), m_color(COLOR_DEFAULT), m_slowdown(1), m_frame(0), m_label() {
		m_frame = new (std::nothrow) Frame[m_max_frame_count];

		if (!m_frame) {
			m_max_frame_count = 0;
			LM.writeLog(IMPORTANT_LVL, "Sprite frame allocation failed.\n");
		}
	}

	//Set width of sprite.
	void Sprite::setWidth(int new_width) {
		m_width = new_width;
	}

	//Get width of sprite.
	int Sprite::getWidth() const {
		return m_width;
	}


	//Set height of sprite.
	void Sprite::setHeight(int new_height) {
		m_height = new_height;
	}

	//Get height of sprite.
	int Sprite::getHeight() const {
		return m_height;
	}

	//Set sprite color
	void Sprite::setColor(Color new_color) {
		m_color = new_color;
	}

	//Get sprite color
	Color Sprite::getColor() const {
		return m_color;
	}

	// Get total count of frames in sprite.
	int Sprite::getFrameCount() const {
		return m_frame_count;
	}

	// Add frame to sprite.
	// Return -1 if frame array full, else 0.
	int Sprite::addFrame(Frame new_frame) {
		if (m_frame_count >= m_max_frame_count) //Is sprite full?
			return -1;

		m_frame[m_frame_count++] = new_frame;

		return 0;
	}

	//Get next sprite frame indicated by number.
	//Return empty frame if out of range [0, m_frame_count -1];
	Frame Sprite::getFrame(int frame_number) const {
		if ((frame_number < 0) || (frame_number >= m_frame_count)) {
			return Frame(); //Return empty frame.
		}

		return m_frame[frame_number];
	}

	//Set label associated with sprite.
	void Sprite::setLabel(std::string new_label) {
		m_label = new_label;
	}

	//Get label associated with sprite.
	std::string Sprite::getLabel() const {
		return m_label;
	}

	//Set animation slowdown value.
	//Value in multiples of GameManager frame time.
	void Sprite::setSlowdown(int new_sprite_slowdown) {
		m_slowdown = new_sprite_slowdown;
	}

	//Get animation slowdown value.
	//Value in multiples of GameManager frame time.
	int Sprite::getSlowdown() const {
		return m_slowdown;
	}

	//Draw indicated frame centered at position.
	//Return 0 if ok, else -1.
	//Note: top-left coordinate is (0,0)
	int Sprite::draw(int frame_number, Vector position) const {
		if ((frame_number < 0) || (frame_number >= m_frame_count)) {
			return -1; //Return empty frame.
		}

		return m_frame[frame_number].draw(position, m_color);
	}
}