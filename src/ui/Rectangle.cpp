#include "ui/Rectangle.h"

namespace ui
{
Rectangle::Rectangle()
    : left(0), top(0), right(0), bottom(0)
{
}

Rectangle::Rectangle(T aLeft, T aTop, T aRight, T aBottom)
    : left(aLeft), top(aTop), right(aRight), bottom(aBottom)
{
}

Rectangle::T Rectangle::getWidth() const
{
    return right - left;
}

Rectangle::T Rectangle::getHeight() const
{
    return top - bottom;
}

bool Rectangle::isIntersection(const Rectangle& rect) const
{
    return
        (left <= rect.right) and
        (right >= rect.left) and
        (bottom <= rect.top) and
        (top >= rect.bottom);
}

bool Rectangle::isValid() const
{
    return (left < right) and (top > bottom);
}

void Rectangle::set(const T aLeft, const T aTop, const T aRight, const T aBottom)
{
    left = aLeft;
    top = aTop;
    right = aRight;
    bottom = aBottom;
}

void Rectangle::offset(const T xOffset, const T yOffset)
{
    top += yOffset;
    bottom += yOffset;
    left += xOffset;
    right += xOffset;
}
}
