#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include <iostream>
#include <fstream>
#include <time.h>
#include "math.h"

#include "vector2D.h"
#include "collisiondata.h"
#include "catapult.h"
#include "graph.h"

class Catapult;
class Graph;

class AI
{
    public:
        AI(float maxforce, Catapult *cata);
        ~AI();

        struct ShotData
        {
            float fForce, fAngle;
        };

        struct AngleData
        {
            bool bHasBeenUsed;

            ShotData shortShot;
            ShotData LongShot;

            float fLastForce;

            AngleData()
            {
                bHasBeenUsed = false;
                shortShot.fForce = 0;
            }
        };

        Catapult *Owner;
        float fMaxForce;
        int iCurrentAngleIndex;
        int iTries;
        int iMinAngle, iMaxAngle;
        int iArraySize;
        AngleData angledata[20];
        Graph *graph;

        void DecideNewForce();
        void InsertData(CollisionData::CollisionType colData);
        void NextAngle();
    private:
};

#endif // AI_H_INCLUDED
