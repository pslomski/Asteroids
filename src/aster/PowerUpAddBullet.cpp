#include "aster/PowerUpAddBullet.hpp"
#include "aster/GameConsts.h"
#include "aster/Ship.hpp"

namespace aster
{
PowerUpAddBullet::PowerUpAddBullet(PlayerShip& playerShip, const Float dt) : ship(playerShip), PowerUp(dt) {}

void PowerUpAddBullet::onStart()
{
    ship.MaxBullets += GE_BULLETS_INCREMENT;
}

void PowerUpAddBullet::onStop()
{
    ship.MaxBullets -= GE_BULLETS_INCREMENT;
}
} // namespace aster
