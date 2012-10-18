#include "ai.h"
#include "game.h"
#include "projectile.h"
#include <iostream>

AI::AI()
{
    currentForce = Vector2D(5, -10);
    baseIndex = MyGame::Instance()->map->GoalIndexRange;
    currentIndex = -1;
    lastVector = Vector2D(0, 0);
};

void AI::DecideNewForce(int currentIndex, Vector2D currentVector)
{
    this->currentIndex = currentIndex;
    this->currentVector = currentVector;

    yIncrease, xIncrease = 0;

    if(lastVector.y < currentVector.y)
    {
        yIncrease = -1;
    } else yIncrease = 5;

    // Calculate X and Y increase
    this->lastVector = lastVector;

    std::cout << "currentIndex: " << currentIndex << std::endl;
    std::cout << "baseIndex.x: " << baseIndex.x << std::endl;
    std::cout << "baseIndex.y: " << baseIndex.y << std::endl;

    this->lastVector = lastVector;

    if(currentIndex < baseIndex.x) // Increase
    {
        currentForce = currentForce + Vector2D(3, yIncrease);
    }
    else if(currentIndex > baseIndex.y) // Decrease
    {
        currentForce = currentForce - Vector2D(1, yIncrease);
    }
    else
    {
        std::cout << "HIT GOAL AT: " << currentIndex << std::endl;
    }
}
