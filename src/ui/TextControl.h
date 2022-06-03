#pragma once

#include <string>

#include "engine/Tools.h"

#include "GameFont.h"
#include "Rectangle.h"

namespace ui
{
// Displays text with an alignment in a specified region
class TextControl
{
public:
    using Rect = ui::Rectanglei;

    TextControl(GameFont* pFont, const Rect& rectPosition);
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
    void update(double currentTime);
    void draw();
    void setTextColor(float red, float green, float blue);
    void setBlink(bool isBlink);
    // The rectangle in which the text is diplayed.
    Rect rect;
private:
    // The font used for the text.
    ui::GameFont* font;
    // The text to display.
    std::string text;
    // The alignment of the text.
    Alignment alignment;

    // The color of the text.
    float red_;
    float green_;
    float blue_;
    bool isBlink_;
    TimeInterval blinkInterval;
};
} // namespace ui
