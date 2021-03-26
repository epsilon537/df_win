#ifndef __DF_DISPLAY_MANAGER_H__
#define __DF_DISPLAY_MANAGER_H__

#include "Manager.h"
#include "Color.h"
#include "Vector.h"
#include "Box.h"
#include <SFML/Graphics.hpp>

// Two-letter acronym for easier access to manager.
#define DM df::DisplayManager::getInstance()

namespace df {
	// Defaults for SFML window.
	const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
	const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
	const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
	const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
	const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar | sf::Style::Close;
	const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
	const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
	const std::string FONT_FILE_DEFAULT = "df-font.ttf";

	enum Justification {
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED
	};

	// Compute character height based on window size and font.
	float charHeight();

	// Compute character width based on window size and font.
	float charWidth();

	// Convert ASCII spaces (x,y) to window pixels
	Vector spacesToPixels(const Vector& spaces);

	// Convert window pixels (x,y) to spaces.
	Vector pixelsToSpaces(const Vector& pixels);

	class DisplayManager : public Manager {
	private:
		DisplayManager();
		DisplayManager(DisplayManager const&);
		void operator=(DisplayManager const&);

		//Returns -1 if fail, 0 otherwise.
		int dragonFlyToSFMLcolor(Color inColor, sf::Color& outColor) const;

		sf::Font m_font; //Font used for ASCII graphics.
		sf::RenderWindow* m_p_window; //Pointer to SFML window.
		int m_window_horizontal_pixels; //Horizontal pixels in window.
		int m_window_vertical_pixels; //Vertical pixels in window.
		int m_window_horizontal_chars; //Horizontal ASCII spaces in window.
		int m_window_vertical_chars; //Vertical ASCII spaces in windows.

	public:
		// Get the one and only instance of the DisplayManager.
		static DisplayManager& getInstance();

		// Open graphics window, ready for text-based display.
		// Return 0 if ok, else -1.
		int startUp();

		// Close graphics window.
		void shutDown();

		// Draw character at world location (x,y) with color.
		// Return 0 if ok, else -1.
		int drawCh(Vector world_pos, char ch, Color color) const;

		// Draw string at world location (x,y) with given color.
		// Justified left, center or right.
		// Return 0 if ok, else -1.
		int drawString(Vector pos, std::string str, Justification just,
			Color color) const;

		// Draw given box, using world coordinates
		// Return 0 if ok, else -1.
		int drawBox(const Box& box, Color color) const;

		// Return window's horizontal max. (in characters).
		int getHorizontal() const;

		// Return window's vertical max. (in character).
		int getVertical() const;

		// Return window's horizontal max (in pixels).
		int getHorizontalPixels() const;

		// Return window's vertical max (in pixels).
		int getVerticalPixels() const;

		// Render current window buffer.
		// Return 0 if ok, else -1.
		int swapBuffers();

		// Return pointer to SFML graphics window.
		sf::RenderWindow* getWindow() const;
	};
}

#endif /*DF_DISPLAY_MANAGER_H*/