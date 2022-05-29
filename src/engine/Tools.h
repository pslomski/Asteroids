#pragma once
#include <string>
#include "Types.h"

///////////////////////////////////////////////////////////////////////////////////////////////

//liczba losowa od 0 do n-1
#define RAND(n) (rand()%(n))

template <typename T>
T CLAMP(const T& what, const T& a, const T& b)
{
	return std::min(b, std::max(what, a));
}
///////////////////////////////////////////////////////////////////////////////////////////////

class TimeInterval {
public:
	TimeInterval(Float in_Interval) { elapsed = 0.0; interval = in_Interval; }
	TimeInterval(void) { elapsed = 0.0; interval = 1.0; }
	Float interval;
	Float elapsed;
	void Reset(void) { elapsed = 0.0; }
	void Reset(Float NewInterval) { elapsed = 0.0; interval = NewInterval; }
	void SetExpired(void) { elapsed = interval + 0.01; }
	bool Inc(Float dt) { elapsed += dt; return elapsed >= interval; }//true jezeli przekroczylo zadany czas
	Float Ratio(void) { return elapsed / interval; }
};

///////////////////////////////////////////////////////////////////////////////////////////////

bool isPointInPolygon(size_t npol, TvecPointF& points, Float x, Float y);
int LinesIntersection(const BoxF& o1, const BoxF& o2, Float& x, Float& y);
PointF geRotate(PointF& pt, Float alfa);
bool setVSync(int interval = 1);
std::string FloatToStr(double val);
std::string GetAppDir(void);
///////////////////////////////////////////////////////////////////////////////////////////////