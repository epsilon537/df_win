#ifndef __DF_TEXT_ENTRY_H__
#define __DF_TEXT_ENTRY_H__

#include "EventKeyboard.h"
#include "ViewObject.h"

namespace df {
	const int TEXT_ENTRY_DEFAULT_BLINK_RATE = 20;

	class TextEntry : public ViewObject {
	private:
		std::string m_text; //Text entered
		std::string m_prefix; //Prefix string going before text entry section.
		int m_limit; //Character limit in text
		bool m_numbers_only; //True if only numbers
		int m_cursor; //Cursor location.
		char m_cursor_char; //Cursor character
		int m_blink_rate; //Cursor blink rate

	public:
		TextEntry(); //Defaults: prefix="", limit=0, numbers_only=false, cursor_char=_,blink_rate=TEXT_ENTRY_DEFAULT_BLINK_RATE

		//Destroy TextEntry object
		virtual ~TextEntry();

		//Set prefix
		void setPrefix(std::string prefix);

		//Get prefix
		std::string getPrefix() const;

		//Set text entered.
		void setText(std::string new_text);

		//Get text entered.
		std::string getText() const;

		//Handle keyboard events.
		//Return 0 if ignored, else 1.
		int eventHandler(const Event* p_e);

		//Called when TextEntry enter hit.
		//Must be defined by derived class.
		virtual void callback() = 0;

		//Set limit of number of characters allowed.
		void setLimit(int new_limit);

		//Get limit of number of characters allowed.
		int getLimit() const;

		//Set cursor to location.
		void setCursor(int new_cursor);

		//Get cursor location.
		int getCursor() const;

		//Set blink rate for cursor (in ticks)
		void setBlinkRate(int new_blink_rate);

		//Get blink rate for cursor
		int getBlinkRate() const;

		//Return true is only numbers can be entered.
		bool numbersOnly() const;

		//Set to allow only numbers to be entered.
		void setNumbersOnly(bool new_numbers_only = true);

		//Set cursor character.
		void setCursorChar(char new_cursor_char);

		//Get cursor character.
		char getCursorChar() const;		
	};
}

#endif /*DF_TEXT_ENTRY_H*/
