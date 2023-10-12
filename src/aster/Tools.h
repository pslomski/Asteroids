#pragma once

#include <string>
#include "Types.h"

// Random number in range 0..n-1
#define RAND(n) (rand() % (n))

bool isPointInPolygon(const size_t nvert, const TvecPointF& verts, const Float testx, const Float testy);
int linesIntersection(const BoxF& o1, const BoxF& o2, Float& x, Float& y);
PointF geRotate(PointF& pt, Float alfa);
