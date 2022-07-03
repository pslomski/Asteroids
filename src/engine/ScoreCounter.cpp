#include "ScoreCounter.hpp"

#include "AsterGame.h"
#include "GameConsts.h"

namespace ge
{
ScoreCounter::ScoreCounter(AsterGame* game_):
    game(game_)
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
} // namespace ge
