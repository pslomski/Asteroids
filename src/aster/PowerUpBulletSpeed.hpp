#pragma once

#include "aster/PowerUp.hpp"

namespace aster
{
class PlayerShip;

class PowerUpBulletSpeed : public PowerUp
{
public:
    PowerUpBulletSpeed(PlayerShip& playerShip, const Float dt);

protected:
    void onStart();
    void onStop();

private:
    PlayerShip& ship;
};
} // namespace aster
