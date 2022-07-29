#include <gtest/gtest.h>

#include "aster/AsterGame.hpp"
#include "aster/ScoreCounter.hpp"

TEST(ScoreCounter, shouldCreate)
{
    aster::AsterGame game;
    aster::ScoreCounter counter(&game);
    ASSERT_EQ(0, counter.get());
}

TEST(ScoreCounter, shouldInc)
{
    aster::AsterGame game;
    aster::ScoreCounter counter(&game);
    counter.inc(2);
    counter.inc(3);
    ASSERT_EQ(5, counter.get());
}

TEST(ScoreCounter, shouldReset)
{
    aster::AsterGame game;
    aster::ScoreCounter counter(&game);
    counter.inc(10);
    counter.reset();
    ASSERT_EQ(0, counter.get());
}
