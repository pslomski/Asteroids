#pragma once

namespace ui
{
class Rectangle {
public:
    using T = int;
    Rectangle();
    Rectangle(const T aLeft, const T aTop, const T aRight, const T aBottom);
    ~Rectangle() { }

    T getWidth() const;
    T getHeight() const;
    bool isIntersection(const Rectangle& rect) const;
    void set(const T aLeft, const T aTop, const T aRight, const T aBottom);
    bool isValid() const;
    void offset(const T xOffset, const T yOffset);

    T top;
    T bottom;
    T left;
    T right;
};
} // namespace ui
