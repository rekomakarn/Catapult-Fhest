#include "vector2D.h"

#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

class AI
{
    public:
        AI();
        ~AI();

        Vector2D baseIndex;
        int currentIndex;

        int currentAngle;
        float currentForce;

        int lastAngle;
        float lastForce;

        void DecideNewForce(int currentIndex, Vector2D currentVector);

    private:
        float forceIncrease;
        float angleIncrease;
};

#endif // AI_H_INCLUDED
