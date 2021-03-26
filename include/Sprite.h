#ifndef __DF_SPRITE_H__
#define __DF_SPRITE_H__

#include "Frame.h"
#include "Color.h"
#include <string>

namespace df {
	class Sprite {
	private:
		int m_width; //Sprite width
		int m_height; // Sprite height
		int m_max_frame_count; //Max number frames sprite can have.
		int m_frame_count; //Actual number of frames sprite has.
		Color m_color; //Sprite color
		int m_slowdown; // Animation slowdown (1=no slowdown, 0=stop).
		Frame* m_frame; //Array of frames.
		std::string m_label; //Text label to identify sprite.
		
		Sprite(); //Don't allow default construction.

	public:
		//Destroy sprite, deleting any allocated frames.
		~Sprite();

		//Create sprite with indicated max. number of frames.
		Sprite(int max_frames);

		//Set width of sprite.
		void setWidth(int new_width);

		//Get width of sprite.
		int getWidth() const;

		//Set height of sprite.
		void setHeight(int new_height);

		//Set height of sprite.
		int getHeight() const;

		//Set sprite color
		void setColor(Color new_color);

		//Get sprite color
		Color getColor() const;

		// Get total count of frames in sprite.
		int getFrameCount() const;

		// Add frame to sprite.
		// Return -1 if frame array full, else 0.
		int addFrame(Frame new_frame);

		//Get next sprite frame indicated by number.
		//Return empty frame if out of range [0, m_frame_count -1];
		Frame getFrame(int frame_number) const;

		//Set label associated with sprite.
		void setLabel(std::string new_label);

		//Get label associated with sprite.
		std::string getLabel() const;

		//Set animation slowdown value.
		//Value in multiples of GameManager frame time.
		void setSlowdown(int new_sprite_slowdown);


		//Get animation slowdown value.
		//Value in multiples of GameManager frame time.
		int getSlowdown() const;

		//Draw indicated frame centered at position.
		//Return 0 if ok, else -1.
		//Note: top-left coordinate is (0,0)
		int draw(int frame_number, Vector position) const;
	};
}
#endif /*DF_SPRITE*/