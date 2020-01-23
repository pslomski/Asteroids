#pragma once

#ifndef _AST_RECTANGLE_H_
#define _AST_RECTANGLE_H_

namespace ast {

	// A simple utility template class which contains information for
	// an axis-aligned rectangle.
	template <class T> class Rectangle {
	public:
		// Default constructor
		Rectangle() : top(0), bottom(0), left(0), right(0) { }
		// Constructor which takes the rectangle coordinates as argument
		Rectangle(T aTop, T aBottom, T aLeft, T aRight)
			: top(aTop), bottom(aBottom), left(aLeft), right(aRight) { }
		~Rectangle() { }

		void set(T aTop, T aBottom, T aLeft, T aRight) { top = aTop; bottom = aBottom; left = aLeft; right = aRight; }
		// Returns the width of the rectangle
		T getWidth()  const { return right - left; }
		// Returns the height of the rectangle
		T getHeight() const { return bottom - top; }

		// Check if this rectangle intersects with the rectangle 
		// passed as argument. Returns true if that's the case.
		bool intersect(const Rectangle& rect) const
		{
			return ((left < rect.right) && (right > rect.left) &&
				(bottom > rect.top) && (top < rect.bottom));
		}

		// Returns true if this is a valid rectangle (has a width and
		// a height).
		bool isValid() const
		{
			if ((top > bottom) || (left > right))
				return false;
			return true;
		}

		void offsetRect(int xOffset, int yOffset)
		{
			top += yOffset;
			bottom += yOffset;
			left += xOffset;
			right += xOffset;
		}

		// The position of the top side of the rectangle
		T  top;
		// The position of the bottom side of the rectangle
		T  bottom;
		// The position of the left side of the rectangle
		T  left;
		// The position of the right side of the rectangle
		T  right;
	};

	// Typedefs for the most used types.
	typedef Rectangle<int>    Rectanglei;
	typedef Rectangle<float>  Rectanglef;
	typedef Rectangle<double> Rectangled;

}//namespace ast

#endif  // _AST_RECTANGLE_H_