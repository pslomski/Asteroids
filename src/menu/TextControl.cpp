#include <math.h>
#include "TextControl.h"
#include "../engine/World.h"
#include "../engine/Consts.h"

CTextControl::CTextControl(ast::GameFont* pFont, const ast::Rectanglei& rectPosition)
	: ptrFont_(pFont), Position(rectPosition), text_(""),
	red_(1.0), green_(1.0), blue_(1.0), blinkInterval_(0.5)
{
	isBlink_ = false;
	textAlign_ = taRight;
}

CTextControl::~CTextControl()
{
}

void CTextControl::Update(double TimeStep)
{
	if (blinkInterval_.Inc(TimeStep)) {
		blinkInterval_.Reset();
	}
}

void CTextControl::Draw()
{
	ast::Rectanglei textSize = ptrFont_->getTextSize(text_);
	int yOffset = Position.getHeight() / 2 + textSize.getHeight() / 2;
	int xOffset = 0;
	switch (textAlign_) {
	case taLeft:
		break;
	case taCenter:
		xOffset = (Position.getWidth() - textSize.getWidth()) / 2;
		break;
	case taRight:
		xOffset = Position.getWidth() - textSize.getWidth();
		break;
	}

	int x = Position.left + xOffset;
	int y = Position.top + yOffset - 5;
	GLfloat fFact = 1.0;
	if (isBlink_) {
		fFact = GLfloat(0.25 * (2.0 + sin(2.0 * GE_PI * blinkInterval_.Ratio())));
	}
	GLColor color(fFact * red_, fFact * green_, fFact * blue_);
	ptrFont_->drawText(text_, x, y, color);
}

void CTextControl::SetTextColor(float red, float green, float blue)
{
	red_ = red;
	green_ = green;
	blue_ = blue;
}

void CTextControl::SetBlink(bool isBlink)
{
	isBlink_ = isBlink;
}