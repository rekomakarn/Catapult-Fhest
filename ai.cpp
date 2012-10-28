#include "ai.h"

AI::AI(float maxforce, Catapult *cata)
{
    fMaxForce = maxforce;
    Owner = cata;
    iMinAngle = 45;
    iMaxAngle = 89;
    iArraySize = 19;
    graph = new Graph(iArraySize, this);
    srand(time(NULL));
}

AI::~AI()
{
    delete graph;
}

void AI::DecideNewForce()
{
    if(iTries == 0)
    {
        angledata[iCurrentAngleIndex].LongShot.fForce = fMaxForce;
        angledata[iCurrentAngleIndex].shortShot.fForce = 0;
        angledata[iCurrentAngleIndex].fLastForce = fMaxForce;
    }

    else
    {
        angledata[iCurrentAngleIndex].fLastForce = angledata[iCurrentAngleIndex].shortShot.fForce + (angledata[iCurrentAngleIndex].LongShot.fForce - angledata[iCurrentAngleIndex].shortShot.fForce) / 2;
    }

    Owner->ChangeForce(angledata[iCurrentAngleIndex].fLastForce);
    Owner->iRotation = iMinAngle + iCurrentAngleIndex * ((iMaxAngle - iMinAngle) / iArraySize);
    Owner->SpawnProjectile();

    iTries++;

    if(iTries > 10)
    {
        NextAngle();
    }
}

void AI::InsertData(CollisionData::CollisionType colData)
{
    if(colData == CollisionData::Long)
    {
        // Did the projectile fly past the target but shorter than the last saved "overshot"?
        if(angledata[iCurrentAngleIndex].LongShot.fForce > angledata[iCurrentAngleIndex].fLastForce)
        {
            // Then replace the larger force.
            angledata[iCurrentAngleIndex].LongShot.fForce = angledata[iCurrentAngleIndex].fLastForce;
        }
    }
    else if (colData == CollisionData::Short)
    {
        // Did the projectile not reach the target, but the force was higher than the old short shot?
        if(angledata[iCurrentAngleIndex].shortShot.fForce < angledata[iCurrentAngleIndex].fLastForce)
        {
            // Then replace the smaller force.
            angledata[iCurrentAngleIndex].shortShot.fForce = angledata[iCurrentAngleIndex].fLastForce;
        }
    }
    else if(colData == CollisionData::Hit)
    {
        NextAngle();
    }

    DecideNewForce();
}

void AI::NextAngle()
{
    // Variables for finding the next point
    int index = 0, lowpoint = 0, highpoint = 0, length = 0;

    // Adds a new point to the graph.
    graph->AddPoint(iCurrentAngleIndex, (angledata[iCurrentAngleIndex].fLastForce / fMaxForce), ((float)iCurrentAngleIndex / (float)iArraySize));

    // Sets the current angledata to used so that can be checked later.
    angledata[iCurrentAngleIndex].bHasBeenUsed = true;

    iTries = 0;

    // The second shot should be the last in the array.
    if(iCurrentAngleIndex == 0)
    {
        iCurrentAngleIndex = iArraySize;
    }
    else
    {
        for(int i = 0; i <= iArraySize; i++)
        {
            // Largest gap between found angles.
            if(angledata[i].bHasBeenUsed)
            {
                if(index > length)
                {
                    lowpoint = i - index;
                    highpoint = i;

                    length = index;
                }

                index = 0;
            }

            index++;
        }

        // Sets the next index to the calculated value.
        iCurrentAngleIndex = lowpoint + ((highpoint - lowpoint) / 2);
    }
}
