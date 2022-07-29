#pragma once

#include <GL/gl.h>

namespace aster
{
class Background
{
public:
    void generate();
    void clear();
    void draw() const;

private:
    GLuint list1{0};
    GLuint list2{0};
};
} // namespace aster
