#include "stdafx.h"
#include "GameFont.h"
#include "../Exception.h"
#include "../engine/renderer.h"

const std::string fontFileName = "vectorb.ttf";

ast::GameFont::GameFont() : ptrFont_(NULL)
{
}

ast::GameFont::~GameFont()
{
	TTF_CloseFont(ptrFont_);
}

void ast::GameFont::createFont(const std::string& fontFace, int height)
{
	ptrFont_ = TTF_OpenFont(fontFileName.c_str(), height);
	if (ptrFont_ == NULL)
		throw SDLException("Couldn't load font");

	// TTF_HINTING_MONO gives best result for vectorb font
	TTF_SetFontHinting(ptrFont_, TTF_HINTING_MONO);
}

ast::Rectanglei ast::GameFont::getTextSize(const std::string& strText)
{
	int w, h;
	TTF_SizeText(ptrFont_, strText.c_str(), &w, &h);
	return ast::Rectanglei(0, h, 0, w);
}

void ast::GameFont::drawText(const std::string& text, int x, int y, GLColor& color)
{
	glColor4fv(color);
	constexpr SDL_Color sdlcolorWhite = { 0xFF, 0xFF, 0xFF, 0 };
	SDL_Color white = sdlcolorWhite;
	// TTF_RenderText_Solid gives best result for vectorb font
	SDL_Surface* surf = TTF_RenderText_Solid(ptrFont_, text.c_str(), white);
	if (surf == NULL)
		throw SDLException("Couldn't render text");

	/* Convert the text into an OpenGL texture */
	GLenum gl_error;
	GLfloat texcoord[4];
	glGetError();
	GLuint texture = ast::Renderer::loadTexture(surf, texcoord);
	if ((gl_error = glGetError()) != GL_NO_ERROR)
		/* If this failed, the text may exceed texture size limits */
		throw std::runtime_error("Warning: Couldn't create texture");

	/* Make texture coordinates easy to understand */
	GLfloat texMinX = texcoord[0];
	GLfloat texMinY = texcoord[1];
	GLfloat texMaxX = texcoord[2];
	GLfloat texMaxY = texcoord[3];
	int w = surf->w;
	int h = surf->h;

	/* We don't need the original text surface anymore */
	SDL_FreeSurface(surf);

	/* Show the text on the screen */
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(texMinX, texMinY); glVertex2i(x, y);
	glTexCoord2f(texMaxX, texMinY); glVertex2i(x + w, y);
	glTexCoord2f(texMinX, texMaxY); glVertex2i(x, y + h);
	glTexCoord2f(texMaxX, texMaxY); glVertex2i(x + w, y + h);
	glEnd();
}

void ast::GameFont::drawFmtText(int x, int y, GLColor& color, const char* fmt, ...)	// Custom GL "Print" Routine
{
	if (fmt == NULL)							// If There's No Text
		return; 								// Do Nothing

	char text[256]; 							// Holds Our String
	va_list	ap;		 							// Pointer To List Of Arguments
	va_start(ap, fmt);							// Parses The String For Variables
	int len = vsprintf_s(text, fmt, ap);		// And Converts Symbols To Actual Numbers
	va_end(ap); 								// Results Are Stored In Text

	drawText(text, x, y, color);
}

