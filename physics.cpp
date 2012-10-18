#include "physics.h"

const float Physics::GRAVITY = 0.3f;

Physics* Physics::pInstance = NULL;

Physics::Physics(void)
{
    return;
}

Physics* Physics::Instance()
{
    return pInstance;
}

void Physics::ApplyGravity(Vector2D &obj)
{
    obj.y += Physics::GRAVITY;
}
