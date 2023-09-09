#include <filesystem>
#include <math.h>
#include "Tools.h"
#include "Consts.h"

///////////////////////////////////////////////////////////////////////////////////////////////
//npol - liczba wierzcholkow wielokata ograniczajacego
//points - wielokat ograniczajacy (ostatni punkt musi byc rozny od pierwszego)
// x, y - badany punkt
//result:
//true - zawiera
//false - nie zawiera
bool isPointInPolygon2(size_t npol, TvecPointF &points, Float x, Float y)
{
    bool result=false;
    int i=0;
    size_t j=npol-1;
    while(i<npol){
        bool bCond1=(points[i].y <= (y)) && ((y) < points[j].y) ||
            (points[j].y <= (y)) && ((y) < points[i].y);
        if(bCond1 &&
          (x < ((points[j].x - points[i].x) * (y - points[i].y) / (points[j].y - points[i].y) + points[i].x)))
            result=!result;
        j=i;
        ++i;
    }
    return result;
}

bool isPointInPolygon(size_t nvert, TvecPointF &verts, Float testx, Float testy)
{
    bool c=false;
    size_t i, j = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((verts[i].y>testy) != (verts[j].y>testy)) &&
            (testx < (verts[j].x-verts[i].x) * (testy-verts[i].y) / (verts[j].y-verts[i].y) + verts[i].x) )
            c = !c;
    }
    return c;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//punkt przeciecica odcinkow
//result
//0 - odcinki sie przecinaja; x, y zawieraja punkt przeciecia
//1 - przeciecie lezy na o1 ale poza o2; x, y zawieraja punkt przeciecia
//2 - przeciecie lezy na o2 ale poza o1; x, y zawieraja punkt przeciecia
//3 - proste sie przecinaja ale poza odcinkami; x, y zawieraja punkt przeciecia
//4 - odcinki sa rownolegle
int linesIntersection(const BoxF &o1, const BoxF &o2, Float &x, Float &y)
{
  Float ua, ub;
  Float la, lb, m;//licznik i mianownik
  m =(o2.y1-o2.y0)*(o1.x1-o1.x0)-(o2.x1-o2.x0)*(o1.y1-o1.y0);
  if(fabs(m)<1e-6){
    //jezeli mianownik=0 wtedy linie sa rownolegle
    return 4;
  }
  la=(o2.x1-o2.x0)*(o1.y0-o2.y0)-(o2.y1-o2.y0)*(o1.x0-o2.x0);
  lb=(o1.x1-o1.x0)*(o1.y0-o2.y0)-(o1.y1-o1.y0)*(o1.x0-o2.x0);

  ua=la/m;
  x=o1.x0+ua*(o1.x1-o1.x0);
  y=o1.y0+ua*(o1.y1-o1.y0);
  ub=lb/m;
  if(       (ua>=0) && (ua<=1) &&  (ub>=0) && (ub<=1))
    return 0;
  else if(  (ua>=0) && (ua<=1) && ((ub<0 ) ||  (ub>1 )))
    return 1;
  else if(((ua<0 ) ||  (ua>1)) &&  (ub>=0) && (ub<=1))
    return 2;
  else
    return 3;
}

PointF geRotate(PointF &pt, Float alfa)
{
    PointF res;
    Float sinalfa=sin(-alfa*GE_PIover180);
    Float cosalfa=cos(-alfa*GE_PIover180);
    res.x=pt.x*cosalfa+pt.y*sinalfa;
    res.y=pt.x*sinalfa+pt.y*cosalfa;
    return res;
}
