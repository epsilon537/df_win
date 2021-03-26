#include "TextEntry.h"
#include "EventStep.h"
#include "utility.h"
#include "LogManager.h"
#include <assert.h>

namespace df {
	TextEntry::TextEntry() : m_text(), m_prefix(), m_limit(0), m_numbers_only(false), m_cursor(0), m_cursor_char('_'), m_blink_rate(TEXT_ENTRY_DEFAULT_BLINK_RATE) {
		registerInterest(STEP_EVENT);
		registerInterest(KEYBOARD_EVENT);
	}

	TextEntry::~TextEntry() {
		ViewObject::~ViewObject();
	}

	//Set prefix
	void TextEntry::setPrefix(std::string prefix) {
		m_prefix = prefix;
		setViewString(m_prefix + m_text);
	}

	//Get prefix
	std::string TextEntry::getPrefix() const {
		return m_prefix;
	}

	//Set text entered.
	void TextEntry::setText(std::string new_text) {
		m_text.assign(new_text, 0, std::string::npos);
		setViewString(m_prefix + m_text);
	}

	//Get text entered.
	std::string TextEntry::getText() const {
		return m_text;
	}

	//Handle keyboard events.
	//Return 0 if ignored, else 1.
	int TextEntry::eventHandler(const Event* p_e) {
		assert(p_e);

		//If step event, blink cursor
		if (p_e->getType() == STEP_EVENT) {
			//LM.writeLog("blink\n");
			//Blink on or off based on rate
			static int blink = -1 * getBlinkRate();
			if (blink >= 0) {
				m_text.replace(m_cursor, 1, 1, getCursorChar());
			}
			else {
				m_text.replace(m_cursor, 1, 1, ' ');
			}

			++blink;

			if (blink == getBlinkRate()) {
				blink = -1 * getBlinkRate();
			}

			setViewString(m_prefix + m_text);

			return 1;
		}

		//If keyboard event, handle
		if ((p_e->getType() == KEYBOARD_EVENT)) {
			const df::EventKeyboard* ek = dynamic_cast<const df::EventKeyboard*>(p_e);
			assert(ek);

			if (ek->getKeyboardAction() == KEY_PRESSED) {
				//If return key pressed, then callback
				if (ek->getKey() == Keyboard::RETURN) {
					callback();
					return 1;
				}

				//If backspace, remove character
				if (ek->getKey() == Keyboard::BACKSPACE) {
					if (m_cursor > 0) {
						m_text.replace(m_cursor, 1, 1, ' ');
						--m_cursor;
						m_text.replace(m_cursor, 1, 1, ' ');

						setViewString(m_prefix + m_text);
					}

					return 1;
				}

				//If not room, cannot add characters.
				if (m_cursor >= m_limit-1) {
					return 1;
				}

				//Get key as string.
				std::string str = toString(ek->getKey());

				//If entry should be number, confirm.
				if (m_numbers_only && !isdigit(str[0])) {
					return 1;
				}

				//Replace with character
				m_text.replace(m_cursor, 1, str);
				setViewString(m_prefix + m_text);

				++m_cursor;

				//All is well
				return 1;
			}
		}

		return 0;
	}

	//Set limit of number of characters allowed.
	void TextEntry::setLimit(int new_limit) {
		m_cursor = 0;
		m_limit = new_limit;
		m_text.clear();
		m_text.resize(m_limit, ' ');
		setViewString(m_prefix + m_text);
	}

	//Get limit of number of characters allowed.
	int TextEntry::getLimit() const {
		return m_limit;
	}

	//Set cursor to location.
	void TextEntry::setCursor(int new_cursor) {
		assert(new_cursor < m_limit);
		m_cursor = new_cursor;
	}

	//Get cursor location.
	int TextEntry::getCursor() const {
		return m_cursor;
	}

	//Set blink rate for cursor (in ticks)
	void TextEntry::setBlinkRate(int new_blink_rate) {
		m_blink_rate = new_blink_rate;
	}

	//Get blink rate for cursor
	int TextEntry::getBlinkRate() const {
		return m_blink_rate;
	}

	//Return true is only numbers can be entered.
	bool TextEntry::numbersOnly() const {
		return m_numbers_only;
	}

	//Set to allow only numbers to be entered.
	void TextEntry::setNumbersOnly(bool new_numbers_only) {
		m_numbers_only = new_numbers_only;
	}

	//Set cursor character.
	void TextEntry::setCursorChar(char new_cursor_char) {
		m_cursor_char = new_cursor_char;
	}

	//Get cursor character.
	char TextEntry::getCursorChar() const {
		return m_cursor_char;
	}
}