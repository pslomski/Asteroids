#include <gtest/gtest.h>

#include "engine/AsterGame.h"
#include "engine/ScoreCounter.hpp"

TEST(ScoreCounter, shouldCreate)
{
    ge::AsterGame game;
    ge::ScoreCounter counter(&game);
    ASSERT_EQ(0, counter.get());
}

TEST(ScoreCounter, shouldInc)
{
    ge::AsterGame game;
    ge::ScoreCounter counter(&game);
    counter.inc(2);
    counter.inc(3);
    ASSERT_EQ(5, counter.get());
}

TEST(ScoreCounter, shouldReset)
{
    ge::AsterGame game;
    ge::ScoreCounter counter(&game);
    counter.inc(10);
    counter.reset();
    ASSERT_EQ(0, counter.get());
}
