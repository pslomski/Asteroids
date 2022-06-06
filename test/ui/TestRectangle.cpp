#include <gtest/gtest.h>

#include "ui/Rectangle.h"

namespace ui
{
class RectangleTest: public ::testing::Test
{ 
public: 
   void SetUp( )
   { 
   }

   void TearDown( )
   { 
   }

   Rectangle rect;
};

TEST_F(RectangleTest, DISABLED_exampleOfDisablingTest)
{
    ASSERT_EQ(0, 1);
}

TEST_F(RectangleTest, testDefaultConstructor)
{
    ASSERT_EQ(0, rect.left);
    ASSERT_EQ(0, rect.top);
    ASSERT_EQ(0, rect.right);
    ASSERT_EQ(0, rect.bottom);
}

TEST_F(RectangleTest, testConstructor2)
{
    int left{1};
    int top{2};
    int right{3};
    int bottom{4};

    Rectangle rect{left, top, right, bottom};

    ASSERT_EQ(left, rect.left);
    ASSERT_EQ(top, rect.top);
    ASSERT_EQ(right, rect.right);
    ASSERT_EQ(bottom, rect.bottom);
}

TEST_F(RectangleTest, testSet)
{
    int left{1};
    int top{2};
    int right{3};
    int bottom{4};

    rect.set(left, top, right, bottom);

    ASSERT_EQ(left, rect.left);
    ASSERT_EQ(top, rect.top);
    ASSERT_EQ(right, rect.right);
    ASSERT_EQ(bottom, rect.bottom);
}

TEST_F(RectangleTest, shouldEvaluateIsValidAsTrue)
{
    int left{1};
    int top{4};
    int right{2};
    int bottom{3};

    rect.set(left, top, right, bottom);
    
    ASSERT_TRUE(rect.isValid());
}

TEST_F(RectangleTest, shouldEvaluateIsValidAsFalseH)
{
    int left{2};
    int top{4};
    int right{1};
    int bottom{3};

    rect.set(left, top, right, bottom);

    ASSERT_FALSE(rect.isValid());
}

TEST_F(RectangleTest, shouldEvaluateIsValidAsFalseV)
{
    int left{1};
    int top{3};
    int right{2};
    int bottom{4};

    rect.set(left, top, right, bottom);

    ASSERT_FALSE(rect.isValid());
}

TEST_F(RectangleTest, shouldGetWidth)
{
    int left{1};
    int top{5};
    int right{2};
    int bottom{3};

    rect.set(left, top, right, bottom);

    ASSERT_EQ(1, rect.getWidth());
}

TEST_F(RectangleTest, shouldGetHeight)
{
    int left{1};
    int top{5};
    int right{2};
    int bottom{3};

    rect.set(left, top, right, bottom);

    ASSERT_EQ(2, rect.getHeight());
}

TEST_F(RectangleTest, testIsIntersection)
{
    Rectangle r1{0, 2, 2, 0};
    Rectangle r2{1, 3, 3, 1};

    ASSERT_TRUE(r1.isIntersection(r2));
}

TEST_F(RectangleTest, shouldOffset)
{
    Rectangle rect{1, 4, 3, 2};

    rect.offset(10, 20);

    ASSERT_EQ(11, rect.left);
    ASSERT_EQ(24, rect.top);
    ASSERT_EQ(13, rect.right);
    ASSERT_EQ(22, rect.bottom);
}
}
