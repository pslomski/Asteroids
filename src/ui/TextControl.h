#pragma once
#include <string>

#include "Font.hpp"
#include "Rectangle.h"
#include "aster/TimeInterval.hpp"
#include "aster/Tools.h"

namespace ui
{
class TextControl
{
public:
    using Rect = Rectangle;

    TextControl(Font* pFont, const Rect& rectPosition);
    ~TextControl();

    enum Alignment
    {
        taLeft,
        taCenter,
        taRight
    };

    void setText(const std::string& value) { text = value; }
    void setAlignement(Alignment textAlign) { alignment = textAlign; }
    void update(const double currentTime);
    void draw();
    void setTextColor(float red, float green, float blue);
    void setBlink(bool isBlink);
    Rect rect;

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
