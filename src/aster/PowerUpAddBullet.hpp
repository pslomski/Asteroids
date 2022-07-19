#pragma once

#include "aster/PowerUp.hpp"

namespace aster
{
class PlayerShip;

class PowerUpAddBullet: public PowerUp
{
public:
    PowerUpAddBullet(PlayerShip& playerShip, const Float dt);

protected:
    void onStart();
    void onStop();

private:
    PlayerShip& ship;
};
} // namespace aster
