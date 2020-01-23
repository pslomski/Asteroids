#ifndef _AST_RENDERER_H_
#define _AST_RENDERER_H_

#include <GL/gl.h>
#include <SDL_ttf.h>

namespace ast {

	class Renderer {
	public:
		static void setWindowSize(int width, int height);
		static void enter2DMode(int width, int height);
		static void leave2DMode();
		static GLuint loadTexture(SDL_Surface* surface, GLfloat* texcoord);
	};

	class DrawMode2DText {
	public:
		DrawMode2DText();
		~DrawMode2DText();
	};

} // namespace ast

#endif // _AST_RENDERER_H_
