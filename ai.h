#include "vector2D.h"

#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

class AI
{
    public:
        Vector2D currentForce;
        Vector2D baseIndex;

        int currentIndex;
        Vector2D currentVector;
        Vector2D lastVector;

        AI();
        void DecideNewForce(int currentIndex, Vector2D currentVector);

    private:
        float yIncrease, xIncrease;
};

#endif // AI_H_INCLUDED
