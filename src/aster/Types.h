#pragma once
#include <GL/gl.h>
#include <vector>

typedef double Float;

template <class T>
class Point
{
public:
    Point() {}

    Point(const Point& p)
    {
        x = p.x;
        y = p.y;
    }

    Point(T in_x, T in_y)
    {
        x = in_x;
        y = in_y;
    }

    T x, y;
};

typedef Point<Float> PointF;

template <class T>
class Box
{
public:
    Box() {}
    Box(const Box& b)
    {
        x0 = b.x0;
        y0 = b.y0;
        x1 = b.x1;
        y1 = b.y1;
    }
    Box(const T in_x0, const T in_y0, const T in_x1, const T in_y1)
    {
        x0 = in_x0;
        y0 = in_y0;
        x1 = in_x1;
        y1 = in_y1;
    }
    T x0, y0, x1, y1;
};

typedef Box<Float> BoxF;

struct Bounds
{
    Float x0, x1, y0, y1;
};

class Color
{
public:
    Color() { Set(); }

    Color(Float in_red, Float in_green, Float in_blue) { Set(in_red, in_green, in_blue); }

    Color(const Color& col)
    {
        r = col.r;
        g = col.g;
        b = col.b;
    }

    Float r, g, b;

    void Set(Float in_red = 1.0, Float in_green = 1.0, Float in_blue = 1.0)
    {
        r = in_red;
        g = in_green;
        b = in_blue;
    }

    Color operator*(const Float k)
    {
        Color col = *this;
        col.r *= k;
        col.g *= k;
        col.b *= k;
        return col;
    }
};

typedef std::vector<PointF> TvecPointF;
typedef std::vector<PointF>::iterator TvecPointFIt;

enum GameState
{
    gsStartGame,
    gsRun,
    gsNextLevelPause,
    gsShipDestroyed,
    gsGameOver
};

enum ObjectGeom
{
    ogPoint,
    ogPolyg
};

enum BonusType
{
    btBullets,
    btBulletSpeed,
    btPoints,
    btLife,
    btNone
};

class GLColor
{
public:
    GLColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0)
    {
        color_[0] = r;
        color_[1] = g;
        color_[2] = b;
        color_[3] = a;
    }
    operator const float*() const { return (float*)color_; }

private:
    GLfloat color_[4];
};
