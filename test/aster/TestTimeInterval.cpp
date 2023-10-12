#include <gtest/gtest.h>

#include "aster/TimeInterval.hpp"

TEST(TimeInterval, shouldCreate)
{
    TimeInterval timeInteval;

    ASSERT_EQ(1.0, timeInteval.get());
}

TEST(TimeInterval, shouldCreate2)
{
    TimeInterval timeInteval{2.0};

    ASSERT_EQ(2.0, timeInteval.get());
}
