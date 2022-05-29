#ifndef _TEXTCONTROL_H_
#define _TEXTCONTROL_H_

#include <string>
#include "Rectangle.h"
#include "GameFont.h"
#include "../engine/Tools.h"


// Utility class that display text with an alignment
// in a specified region.
class CTextControl
{
public:
	CTextControl(ast::GameFont* pFont, const ast::Rectanglei& rectPosition);
	~CTextControl();

	// The text alignment
	enum TextAlign
	{
		taLeft,
		taCenter,
		taRight
	};

	void SetText(const std::string& text)  { text_ = text; }
	void SetAlignement(TextAlign textAlign) { textAlign_ = textAlign; }
	void Update(double currentTime);
	void Draw();
	void SetTextColor(float red, float green, float blue);
	void SetBlink(bool isBlink);
	// The rectangle in which the text is diplayed.
	ast::Rectanglei Position;
private:
	// The font used for the text.
	ast::GameFont* ptrFont_;
	// The text to display.
	std::string text_;
	// The alignment of the text.
	TextAlign textAlign_;

	// The color of the text.
	float red_;
	float green_;
	float blue_;
	bool isBlink_;
	TimeInterval blinkInterval_;
};

#endif // _TEXTCONTROL_H_