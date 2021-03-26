#include "Frame.h"
#include "DisplayManager.h"

namespace df {
	//Create empty frame
	Frame::Frame() : m_width(0), m_height(0), m_frame_str() {

	}

	//Create a frame of indicated with, height and string.
	Frame::Frame(int width, int height, std::string frame_str) :
		m_width(width), m_height(height), m_frame_str(frame_str) {
	}

	//Set width of frame.
	void Frame::setWidth(int new_width) {
		m_width = new_width;
	}

	//Get width of frame.
	int Frame::getWidth() const {
		return m_width;
	}

	//Set height of frame.
	void Frame::setHeight(int new_height) {
		m_height = new_height;
	}

	//Get height of frame.
	int Frame::getHeight() const {
		return m_height;
	}

	//Set frame characters (stored as a string).
	void Frame::setString(std::string new_frame_str) {
		m_frame_str = new_frame_str;
	}

	//Get frame characters (stored as a string).
	std::string Frame::getString() const {
		return m_frame_str;
	}

	//Draw self, centered a position with color.
	//Return 0 if ok, else -1.
	//Top left coordinate is (0,0)
	int Frame::draw(Vector position, Color color) const {
		if (m_frame_str.empty())
			return -1;

		float x_offset = (float)m_width/2;
		float y_offset = (float)m_height/2;

		//Draw character by character
		for (int y=0; y < m_height; y++) {
			for (int x = 0; x < m_width; x++) {
				Vector temp_pos = Vector(position.getX() + x - x_offset,
					position.getY() + y - y_offset);
				DM.drawCh(temp_pos, m_frame_str[y * m_width + x], color);
			}
		}

		return 0;
	}

	//Returns true if this is an empty frame.
	bool Frame::isEmpty() const {
		return m_frame_str.empty();
	}
}