#include "Background.hpp"

#include "aster/Tools.h"
#include "aster/Types.h"
#include "aster/World.h"

namespace aster
{
void Background::clear()
{
    if (list1)
    {
        glDeleteLists(list1, 1);
    }
    list1 = 0;
    if (list2)
    {
        glDeleteLists(list2, 1);
    }
    list2 = 0;
}

void Background::generate()
{
    int w = int(geWorld.getWidth());
    int h = int(geWorld.GetHeight());
    if (list1 == 0)
    {
        list1 = glGenLists(1);
        glNewList(list1, GL_COMPILE);
        Float col = 0.4 + RAND(21) / 20;
        glColor3d(col, col, col);
        glBegin(GL_POINTS);
        for (int i = 0; i < 50; ++i)
        {
            glVertex2d(rand() % w, rand() % h);
        }
        glEnd();
        glEndList();
    }
    if (list2 == 0)
    {
        list2 = glGenLists(1);
        glNewList(list2, GL_COMPILE);
        glBegin(GL_POINTS);
        Float col = 0.6 + RAND(21) / 20;
        glColor3d(col, col, col);
        for (int i = 0; i < 50; ++i)
        {
            glVertex2d(rand() % w, rand() % h);
        }
        glEnd();
        glEndList();
    }
}

void Background::draw() const
{
    glPointSize(1);
    glCallList(list1);
    glPointSize(2);
    glCallList(list2);
}
} // namespace aster
