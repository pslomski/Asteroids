#pragma once
#include <string>
#include "Types.h"

// Random number in range 0..n-1
#define RAND(n) (rand() % (n))

bool isPointInPolygon(size_t npol, TvecPointF& points, Float x, Float y);
int LinesIntersection(const BoxF& o1, const BoxF& o2, Float& x, Float& y);
PointF geRotate(PointF& pt, Float alfa);
bool setVSync(int interval = 1);
std::string FloatToStr(double val);
std::string getAppDir(void);
