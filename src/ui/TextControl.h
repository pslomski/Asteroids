#pragma once

#include <string>

#include "engine/Tools.h"

#include "Font.h"
#include "Rectangle.h"

namespace ui
{
// Displays text with an alignment in a specified region
class TextControl
{
public:
    using Rect = Rectangle;

    TextControl(Font* pFont, const Rect& rectPosition);
    ~TextControl();

    // The text alignment
    enum Alignment
    {
        taLeft,
        taCenter,
        taRight
    };

    void setText(const std::string& value)  { text = value; }
    void setAlignement(Alignment textAlign) { alignment = textAlign; }
    void update(const double currentTime);
    void draw();
    void setTextColor(float red, float green, float blue);
    void setBlink(bool isBlink);
    Rect rect; // The rectangle in which the text is diplayed.
private:
    Font* font;
    std::string text;
    Alignment alignment;
    float red_;
    float green_;
    float blue_;
    bool isBlink_;
    TimeInterval blinkInterval;
};
} // namespace ui
