#pragma once

#include <string>
#include "Types.h"

// Random number in range 0..n-1
#define RAND(n) (rand() % (n))

bool isPointInPolygon(size_t npol, TvecPointF& points, Float x, Float y);
int linesIntersection(const BoxF& o1, const BoxF& o2, Float& x, Float& y);
PointF geRotate(PointF& pt, Float alfa);
