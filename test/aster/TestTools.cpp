#include "gtest/gtest.h"
#include <gtest/gtest.h>

#include "aster/Tools.h"

namespace testing
{
struct TestIsPointInPolygonParam
{
    size_t npol{0};
    TvecPointF points{};
    Float x{0.0};
    Float y{0.0};
    bool expected{};
};

class TestIsPointInPolygon: public testing::TestWithParam<TestIsPointInPolygonParam>
{
};

TEST_P(TestIsPointInPolygon, evaluate)
{
    ASSERT_EQ(isPointInPolygon(GetParam().npol, GetParam().points, GetParam().x, GetParam().y), GetParam().expected);
}

INSTANTIATE_TEST_CASE_P(
    isPointInPolygon,
    TestIsPointInPolygon,
    Values(
        TestIsPointInPolygonParam{.npol = 4, .points = {{1, 1}, {-1, 1}, {-1,-1}, {1,-1}}, .x = 0.0, .y = 0.0, .expected =  true},
        TestIsPointInPolygonParam{.npol = 4, .points = {{1, 1}, {-1, 1}, {-1,-1}, {1,-1}}, .x = 0.999999, .y = 0.999999, .expected = true},
        TestIsPointInPolygonParam{.npol = 4, .points = {{1, 1}, {-1, 1}, {-1,-1}, {1,-1}}, .x = 1.0, .y = 1.0, .expected = false},
        TestIsPointInPolygonParam{.npol = 4, .points = {{1, 1}, {-1, 1}, {-1,-1}, {1,-1}}, .x = -1.0, .y = -1.0, .expected = true}
    )
);
}
