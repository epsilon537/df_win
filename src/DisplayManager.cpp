#include "DisplayManager.h"
#include "LogManager.h"
#include "utility.h"

namespace df { 
	// Compute character height based on window size and font.
	float charHeight() {
		return (float)(DM.getVerticalPixels())/ DM.getVertical();
	}

	// Compute character width based on window size and font.
	float charWidth() {
		return (float)(DM.getHorizontalPixels()) / DM.getHorizontal();
	}

	// Convert ASCII spaces (x,y) to window pixels
	Vector spacesToPixels(const Vector& spaces) {
		return Vector(spaces.getX() * charWidth(), spaces.getY() * charHeight());
	}

	// Convert window pixels (x,y) to spaces.
	Vector pixelsToSpaces(const Vector& pixels) {
		return Vector(pixels.getX()/charWidth(), pixels.getY()/charHeight());
	}

	DisplayManager::DisplayManager() : 
		m_window_horizontal_pixels(WINDOW_HORIZONTAL_PIXELS_DEFAULT), m_window_vertical_pixels(WINDOW_VERTICAL_PIXELS_DEFAULT),
		m_window_horizontal_chars(WINDOW_HORIZONTAL_CHARS_DEFAULT), m_window_vertical_chars(WINDOW_VERTICAL_CHARS_DEFAULT) {
		setType("DisplayManager");
	}

	// Get the singletone instance.
	DisplayManager& DisplayManager::getInstance() {
		static DisplayManager displayManager;
		return displayManager;
	}

	// Open graphics window, ready for text-based display.
	// Return 0 if ok, else -1.
	int DisplayManager::startUp() {

		//If window already created, do nothing.
		if (m_p_window)
			return 0;

		m_p_window = new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels), 
			WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);

		if (!m_p_window) {
			LM.writeLog("Failed to create RenderWindow.\n");
			return -1;
		}

		//Turn off mouse cursor for window.
		m_p_window->setMouseCursorVisible(false);

		//Set vertical sync
		m_p_window->setVerticalSyncEnabled(true);

		if (!m_font.loadFromFile(FONT_FILE_DEFAULT)) {
			LM.writeLog("Failed to load font %s.\n", FONT_FILE_DEFAULT);
			return -1;
		}

		Manager::startUp();
		return 0;
	}

	// Close graphics window.
	void DisplayManager::shutDown() {
		if (m_p_window)
			m_p_window->close();
	}

	//Returns -1 if fail, 0 otherwise.
	int DisplayManager::dragonFlyToSFMLcolor(Color inColor, sf::Color& outColor) const {
		// Set SFML color based on Dragonfly color.
		switch (inColor) {
		case YELLOW:
			outColor = sf::Color::Yellow;
			break;

		case RED:
			outColor = sf::Color::Red;
			break;

		case GREEN:
			outColor = sf::Color::Green;
			break;

		case BLACK:
			outColor = sf::Color::Black;
			break;

		case BLUE:
			outColor = sf::Color::Blue;
			break;

		case MAGENTA:
			outColor = sf::Color::Magenta;
			break;

		case CYAN:
			outColor = sf::Color::Cyan;
			break;

		case WHITE:
			outColor = sf::Color::White;
			break;

		default:
			LM.writeLog("Invalid color :%d\n", int(inColor));
			return -1;
		}

		return 0;
	}

	// Draw character at world location (x,y) with color.
	// Return 0 if ok, else -1.
	int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {
		if (!m_p_window)
			return -1;

		Vector view_pos = worldToView(world_pos);

		Vector pixel_pos = spacesToPixels(view_pos);

		//Draw background rectangle since text is see through in SFML. FIXME: Do we need this?
		static sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
		rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
		rectangle.setPosition(
			sf::Vector2f(pixel_pos.getX() - charWidth()/10,
				pixel_pos.getY() + charHeight()/10));
		m_p_window->draw(rectangle);

		// Create character text to draw.
		static sf::Text text("", m_font);
		text.setString(ch);
		text.setStyle(sf::Text::Bold);

		// Scale to right size.
		if (charWidth() < charHeight())
			text.setCharacterSize((unsigned)charWidth() * 2);
		else
			text.setCharacterSize((unsigned)charHeight() * 2);

		// Set SFML color based on Dragonfly color.
		sf::Color sfmlColor;
		if (dragonFlyToSFMLcolor(color, sfmlColor) == -1)
			return -1;

		text.setFillColor(sfmlColor);

		// Set position in window (in pixels)
		text.setPosition(sf::Vector2f(pixel_pos.getX(), pixel_pos.getY()));
	
		// Draw character.
		m_p_window->draw(text);

		return 0;
	}

	// Draw string at window location (x,y) with default color.
	// Justified left, center or right.
	// Return 0 if ok, else -1.
	int DisplayManager::drawString(Vector pos, std::string str, Justification just,
		Color color) const {
		Vector starting_pos = pos;
	
		switch (just) {
			case CENTER_JUSTIFIED:
				starting_pos.setX(pos.getX() - str.size()/2);
				break;
			case RIGHT_JUSTIFIED:
				starting_pos.setX(pos.getX() - str.size());
				break;
			case LEFT_JUSTIFIED:
			default:
				break;
		}

		// Draw string character by character.
		for (int ii = 0; ii < str.length(); ii++) {
			Vector temp_pos(starting_pos.getX() + ii, starting_pos.getY());
			drawCh(temp_pos, str[ii], color);
		}

		return 0;
	}

	// Draw given box, using world coordinates
	// Return 0 if ok, else -1
	int DisplayManager::drawBox(const Box& box, Color color) const {

		if (!m_p_window)
			return -1;

		Vector view_pos = worldToView(box.getCorner());

		Vector pixel_pos = spacesToPixels(view_pos);

		static sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(box.getHorizontal()*charWidth(), box.getVertical()*charHeight()));
		rectangle.setOutlineThickness(1);

		sf::Color sfmlColor;
		if (dragonFlyToSFMLcolor(color, sfmlColor) == -1)
			return -1;

		rectangle.setOutlineColor(sfmlColor);
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setPosition(
			sf::Vector2f(pixel_pos.getX() /*- charWidth() / 10*/, pixel_pos.getY() /*+ charHeight() / 10)*/));
		m_p_window->draw(rectangle);

		return 0;
	}

	// Return window's horizontal max. (in characters).
	int DisplayManager::getHorizontal() const {
		return m_window_horizontal_chars;
	}

	// Return window's vertical max. (in character).
	int DisplayManager::getVertical() const {
		return m_window_vertical_chars;
	}

	// Return window's horizontal max (in pixels).
	int DisplayManager::getHorizontalPixels() const {
		return m_window_horizontal_pixels;
	}

	// Return window's vertical max (in pixels).
	int DisplayManager::getVerticalPixels() const {
		return m_window_vertical_pixels;
	}

	// Render current window buffer.
	// Return 0 if ok, else -1.
	int DisplayManager::swapBuffers() {
		if (!m_p_window)
			return -1;


		//Display current window
		m_p_window->display();

		//Clear other window to get ready for next draw.
		m_p_window->clear();

		return 0;
	}

	// Return pointer to SFML graphics window.
	sf::RenderWindow* DisplayManager::getWindow() const {
		return m_p_window;
	}
}