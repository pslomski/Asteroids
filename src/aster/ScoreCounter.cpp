#include "ScoreCounter.hpp"

#include "AsterGame.hpp"
#include "GameConsts.h"

namespace aster
{
ScoreCounter::ScoreCounter(AsterGame* asterGame) : game(asterGame)
{
    reset();
}

void ScoreCounter::inc(const int points)
{
    score += points;
    if (score >= nextLife)
    {
        nextLife += GE_NEXT_LIFE_SCORE;
        game->Lives++;
        level++;
    }
}

int ScoreCounter::get()
{
    return score;
}

void ScoreCounter::reset()
{
    score = 0;
    nextLife = GE_NEXT_LIFE_SCORE;
    level = 1;
}
} // namespace aster
