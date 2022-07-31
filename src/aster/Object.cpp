#include <assert.h>
#include "Object.h"
#include "World.h"
#include "Tools.h"
#include "Consts.h"

Float Object::dt = 0.0;

Object::Object():
    ScoreValue(0),
    ObjGeom(ogPoint),
    glList(0),
    falfa(0.0),
    fomega(0.0),
    KDec(0.0)
{
    color();
    SetXY(0.0, 0.0);
    SetA(0.0);
    SetV(0.0);
}

Float Object::distance(const Object* object) const
{
    const Float dx = object->fx - fx;
    const Float dy = object->fy - fy;
    return sqrt(dx * dx + dy * dy);
}

void Object::SetA(Float aa)
{
    fa = aa;
    fax = Float(fa * cos(falfa * GE_PIover180));
    fay = Float(fa * sin(falfa * GE_PIover180));
}

void Object::SetV(Float av)
{
    fv = av;
    fvx = Float(fv * cos(falfa * GE_PIover180));
    fvy = Float(fv * sin(falfa * GE_PIover180));
}

void Object::SetVA(Float av, Float alfa)
{
    fv = av;
    fvx = Float(fv * cos(alfa * GE_PIover180));
    fvy = Float(fv * sin(alfa * GE_PIover180));
}

void Object::SetRandV(Float vmin, Float vmax)
{
    Float vRand = rand() % int(vmax - vmin) + vmin;
    Float alfa = rand() % 360;
    Float vx = vRand * cos(alfa * GE_PIover180);
    Float vy = vRand * sin(alfa * GE_PIover180);
    SetV(vx, vy);
}

Float Object::CorrectAlfa(Float alfa)
{
    while (alfa < 0.0)
        alfa += 360.0;
    while (alfa > 360.0)
        alfa -= 360.0;
    return alfa;
}

void Object::Move()
{
    xp = fx;
    yp = fy;
    alphap = falfa;

    falfa += fomega * dt;
    if (abs(KDec) > 1e-6)
    {
        fvx += (fax - KDec * fvx * abs(fvx)) * dt;
        fvy += (fay - KDec * fvy * abs(fvy)) * dt;
    }
    else
    {
        fvx += fax * dt;
        fvy += fay * dt;
    }
    fx += fvx * dt;
    fy += fvy * dt;

    if (fx < geWorld.clipLeft)
    {
        fx += geWorld.clipRight;
        xp += geWorld.clipRight;
    }
    if (fx > geWorld.clipRight)
    {
        fx -= geWorld.clipRight;
        xp -= geWorld.clipRight;
    }
    if (fy < geWorld.clipBottom)
    {
        fy += geWorld.clipTop;
        yp += geWorld.clipTop;
    }
    if (fy > geWorld.clipTop)
    {
        fy -= geWorld.clipTop;
        yp -= geWorld.clipTop;
    }
}

BoxF Object::Transform(const BoxF &seg) const
{
    BoxF res;
    Float sinalfa = sin(-falfa * GE_PIover180);
    Float cosalfa = cos(-falfa * GE_PIover180);
    res.x0 = fx + seg.x0 * cosalfa + seg.y0 * sinalfa;
    res.y0 = fy - seg.x0 * sinalfa + seg.y0 * cosalfa;
    res.x1 = fx + seg.x1 * cosalfa + seg.y1 * sinalfa;
    res.y1 = fy - seg.x1 * sinalfa + seg.y1 * cosalfa;
    return res;
}

bool _CheckPolygWithPoint(Object *pObjPoint, Object *pObjPolyg)
{
    BoxF o1;
    Float x, y;
    // bierzemy wektor przesuniecia punktu
    BoxF o2 = BoxF(pObjPoint->xp, pObjPoint->yp, pObjPoint->GetX(), pObjPoint->GetY());
    for (unsigned int i1 = 0; i1 < pObjPolyg->Verts.size(); ++i1)
    {
        if (0 == i1)
        {
            o1 = pObjPolyg->Transform(
                BoxF(
                    pObjPolyg->Verts[0].x,
                    pObjPolyg->Verts[0].y,
                    pObjPolyg->Verts[pObjPolyg->Verts.size() - 1].x,
                    pObjPolyg->Verts[pObjPolyg->Verts.size() - 1].y));
        }
        else
        {
            o1 = pObjPolyg->Transform(
                BoxF(
                    pObjPolyg->Verts[i1 - 1].x,
                    pObjPolyg->Verts[i1 - 1].y,
                    pObjPolyg->Verts[i1].x,
                    pObjPolyg->Verts[i1].y));
        }
        if (LinesIntersection(o1, o2, x, y) == 0)
        {
            return true;
        }
        else
        {
            PointF pt(pObjPoint->GetX() - pObjPolyg->GetX(), pObjPoint->GetY() - pObjPolyg->GetY());
            pt = geRotate(pt, -pObjPolyg->GetAlfa());
            return isPointInPolygon(pObjPolyg->Verts.size(), pObjPolyg->Verts, pt.x, pt.y);
        }
    }
    return false;
}

bool Object::CheckCollision(Object *pObiekt)
{
    assert(NULL != pObiekt);

    if (((GetX() + Bounds.x0) > (pObiekt->GetX() + pObiekt->Bounds.x1)) ||
        ((GetX() + Bounds.x1) < (pObiekt->GetX() + pObiekt->Bounds.x0)) ||
        ((GetY() + Bounds.y0) > (pObiekt->GetY() + pObiekt->Bounds.y1)) ||
        ((GetY() + Bounds.y1) < (pObiekt->GetY() + pObiekt->Bounds.y0)))
        return false;
    else
    {
        if (ogPolyg == ObjGeom)
        {
            BoxF o1, o2;
            Float _x, _y;
            if (ogPolyg == pObiekt->ObjGeom)
            {
                for (unsigned int i1 = 0; i1 < Verts.size(); ++i1)
                {
                    if (0 == i1)
                        o1 = Transform(BoxF(Verts[0].x, Verts[0].y, Verts[Verts.size() - 1].x, Verts[Verts.size() - 1].y));
                    else
                        o1 = Transform(BoxF(Verts[i1 - 1].x, Verts[i1 - 1].y, Verts[i1].x, Verts[i1].y));
                    for (unsigned int i2 = 0; i2 < pObiekt->Verts.size(); ++i2)
                    {
                        if (0 == i2)
                            o2 = pObiekt->Transform(BoxF(pObiekt->Verts[0].x, pObiekt->Verts[0].y, pObiekt->Verts[pObiekt->Verts.size() - 1].x, pObiekt->Verts[pObiekt->Verts.size() - 1].y));
                        else
                            o2 = pObiekt->Transform(BoxF(pObiekt->Verts[i2 - 1].x, pObiekt->Verts[i2 - 1].y, pObiekt->Verts[i2].x, pObiekt->Verts[i2].y));
                        if (LinesIntersection(o1, o2, _x, _y) == 0)
                            return true;
                    }
                }
            }
            else if (ogPoint == pObiekt->ObjGeom)
            {
                if (_CheckPolygWithPoint(pObiekt, this))
                    return true;
            }
            else
            {
                return true; // przyjmyjemy przeciecie Bounds za kolizje
            }
        }
        else if (ogPoint == ObjGeom)
        {
            if (ogPolyg == pObiekt->ObjGeom)
            {
                if (_CheckPolygWithPoint(this, pObiekt))
                    return true;
            }
            else
                return true; // w przypadku 2 punktow przyjmyjemy przeciecie Bounds za kolizje
        }
        else
        {
            return true; // przyjmyjemy przeciecie Bounds za kolizje
        }
        return false;
    }
}

void Object::Draw()
{
    Float minterp = 1.0 - geWorld.interp;
    Float x = fx * geWorld.interp + xp * minterp;
    Float y = fy * geWorld.interp + yp * minterp;
    Float alfa = falfa * geWorld.interp + alphap * minterp;

    glPushMatrix();
    glTranslated(x, y, 0.0);
    glRotated(alfa, 0.0, 0.0, 1.0);

    OnRender();

    glPopMatrix();
}

void Object::Render()
{
    OnRender();
}

void Object::CalcBounds(TvecPointF &Verts)
{
    Float Max = 0.0;
    for (TvecPointFIt it = Verts.begin(); it != Verts.end(); ++it)
    {
        Max = std::max(Max, abs((*it).x));
        Max = std::max(Max, abs((*it).y));
    }
    Bounds.x0 = -Max;
    Bounds.x1 = Max;
    Bounds.y0 = -Max;
    Bounds.y1 = Max;
}
