#pragma once

#ifndef _GAMEFONT_H_
#define _GAMEFONT_H_

#include <SDL_ttf.h>
#include <string>
#include "../engine/Types.h"
#include "Rectangle.h"

namespace ast {

	// Utility class used to draw text on the screen using a specific font.
	class GameFont {
	public:
		GameFont();
		GameFont(const std::string& fontFace, int height) {
			createFont(fontFace, height);
		}
		~GameFont();

		// Draw text on the screen at the specified location with
		// the specified colour.
		void drawText(const std::string& text, int x, int y, GLColor& color);
		void drawFmtText(int x, int y, GLColor& color, const char* fmt, ...);

		// Returns the size of the text. The top and right fields
		// of the returned rectangle are set to 0.
		ast::Rectanglei getTextSize(const std::string& text);
	private:
		// Create the font with a specific height.
		void createFont(const std::string& fontFace, int height);

		TTF_Font* ptrFont_;
	};

} // namespace ast

#endif  // _GAMEFONT_H_