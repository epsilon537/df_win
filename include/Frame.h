#ifndef __DF_FRAME_H__
#define __DF_FRAME_H__

#include <string>
#include <Vector.h>
#include <Color.h>

namespace df {
	class Frame {
	private:
		int m_width;  //Width of a frame.
		int m_height; //Height of a frame.
		std::string m_frame_str; //All frame characters stored as a string.
	
	public:
		//Create empty frame
		Frame();

		//Create a frame of indicated with, height and string.
		Frame(int width, int height, std::string frame_str);

		//Set width of frame.
		void setWidth(int new_width);

		//Get width of frame.
		int getWidth() const;

		//Set height of frame.
		void setHeight(int new_height);

		//Get height of frame.
		int getHeight() const;

		//Set frame characters (stored as a string).
		void setString(std::string new_frame_str);

		//Get frame characters (stored as a string).
		std::string getString() const;

		//Draw self, centered a position with color.
		//Return 0 if ok, else -1.
		//Top left coordinate is (0,0)
		int draw(Vector position, Color color) const;

		//Returns true if this is an empty frame.
		bool isEmpty() const;
	};
}

#endif /*DF_FRAME*/