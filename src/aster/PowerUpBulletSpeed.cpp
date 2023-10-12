#include "aster/PowerUpBulletSpeed.hpp"
#include "aster/GameConsts.h"
#include "aster/Ship.hpp"

namespace aster
{
PowerUpBulletSpeed::PowerUpBulletSpeed(PlayerShip& playerShip, const Float dt) : ship(playerShip), PowerUp(dt) {}

void PowerUpBulletSpeed::onStart()
{
    ship.BulletSpeed += GE_BULLET_SPEED_INC;
}

void PowerUpBulletSpeed::onStop()
{
    ship.BulletSpeed -= GE_BULLET_SPEED_INC;
}
} // namespace aster
