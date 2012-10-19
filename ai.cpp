#include "ai.h"
#include "game.h"
#include "projectile.h"
#include <iostream>

AI::AI()
{
    /*if(MyGame::Instance())
        std::cout << "AI::AI() MyGame instance found!" << std::endl;
        //baseIndex = MyGame::Instance()->map->GoalIndexRange;
    else
        std::cout << "AI::AI() map in MyGame instance not found!" << std::endl;*/

    currentIndex = -1;

    currentForce = 0.0f;
    currentAngle = 0;

    lastForce = 0.0f;
    lastAngle = 0;
};

AI::~AI()
{

}

void AI::DecideNewForce(int currentIndex, Vector2D currentVector)
{
    //this->currentIndex = currentIndex;
    /*this->currentVector = currentVector;

    forceIncrease, angleIncrease = 0;

    if(currentIndex < baseIndex.x) // Increase
    {
        // Increase force here
    }
    else if(currentIndex > baseIndex.y) // Decrease
    {
        // Decrease force here
    }
    else // It hit the target!
    {
        std::cout << "HIT GOAL AT: " << currentIndex << std::endl;
    }*/
}
