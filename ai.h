#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "vector2D.h"
#include "collisiondata.h"

class AI
{
    public:
        AI();
        ~AI();

        void DecideNewForce(int currentIndex, Vector2D currentVector);

        struct ShotData
        {
            float fForce, fAngle;
        };
    private:
};

#endif // AI_H_INCLUDED
