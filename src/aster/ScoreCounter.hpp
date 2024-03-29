#pragma once

namespace aster
{
class AsterGame;
class ScoreCounter
{
public:
    ScoreCounter(AsterGame*);

    void reset();
    int get();
    void inc(const int points);

private:
    AsterGame* game;
    int score;
    int nextLife;
    int level;
};
} // namespace aster
