#include <math.h>

#include "aster/Consts.h"
#include "aster/World.h"

#include "ui/TextControl.h"

namespace ui
{
TextControl::TextControl(Font* pFont, const Rect& rectPosition)
    : font(pFont)
    , rect(rectPosition)
    , text("")
    , red_(1.0)
    , green_(1.0)
    , blue_(1.0)
    , blinkInterval(0.5)
    , isBlink_(false)
    , alignment(taRight)
{
}

TextControl::~TextControl() {}

void TextControl::update(const double TimeStep)
{
    if (blinkInterval.inc(TimeStep))
    {
        blinkInterval.reset();
    }
}

void TextControl::draw()
{
    Font::Size textSize = font->getTextSize(text);
    int yOffset = rect.getHeight() / 2 + textSize.height / 2;
    int xOffset = 0;
    switch (alignment)
    {
        case taLeft:
            break;
        case taCenter:
            xOffset = (rect.getWidth() - textSize.width) / 2;
            break;
        case taRight:
            xOffset = rect.getWidth() - textSize.width;
            break;
    }

    int x = rect.left + xOffset;
    int y = rect.top + yOffset - 5;
    GLfloat fFact = 1.0;
    if (isBlink_)
    {
        fFact = GLfloat(0.25 * (2.0 + sin(2.0 * GE_PI * blinkInterval.ratio())));
    }
    GLColor color(fFact * red_, fFact * green_, fFact * blue_);
    font->drawText(text, x, y, color);
}

void TextControl::setTextColor(float red, float green, float blue)
{
    red_ = red;
    green_ = green;
    blue_ = blue;
}

void TextControl::setBlink(bool isBlink)
{
    isBlink_ = isBlink;
}
} // namespace ui
