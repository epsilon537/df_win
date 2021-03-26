#ifndef __DF_COLOR_H__
#define __DF_COLOR_H__

namespace df {
	// Colors Dragonfly recognizes.
	enum Color {
		UNDEFINED_COLOR = -1,
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
	};

	// If color not specified, use this
	const Color COLOR_DEFAULT = WHITE;
}

#endif /*DF_COLOR_H*/