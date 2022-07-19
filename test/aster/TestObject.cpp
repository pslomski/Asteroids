#include <gtest/gtest.h>

#include "aster/Object.h"

TEST(Object, distance)
{
    Object o1, o2;
    o1.SetXY(0, 0);
    o2.SetXY(1, 0);
    ASSERT_EQ(1, o1.distance(&o2));
}
