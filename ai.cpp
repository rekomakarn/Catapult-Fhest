#include "ai.h"

AI::AI(float maxforce, Catapult *cata)
{
    fMaxForce = maxforce;
    Owner = cata;
    iMinAngle = 45;
    iMaxAngle = 89;
    iArraySize = 19;
    iTries = 0;
    iCurrentAngleIndex = 0;
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
        angledata[iCurrentAngleIndex].fLastForce = fMaxForce;

        if(iCurrentAngleIndex == 0 || iCurrentAngleIndex == iArraySize)
        {
            angledata[iCurrentAngleIndex].shortShot.fForce = 0;
        }
        else
        {
            int lowerIndex = 0, higherIndex = 0;

            for(int i = iCurrentAngleIndex; i > 0; i--)
            {
                if(angledata[i].bHasBeenUsed)
                {
                    lowerIndex = i;
                    break;
                }
            }

            for(int i = iCurrentAngleIndex; i < iArraySize; i++)
            {
                if(angledata[i].bHasBeenUsed)
                {
                    higherIndex = i;
                    break;
                }
            }
            angledata[iCurrentAngleIndex].shortShot.fForce = (angledata[lowerIndex].fLastForce + ((angledata[higherIndex].fLastForce - angledata[lowerIndex].fLastForce) / 2)) / 2;
        }
    }

    else
    {
        angledata[iCurrentAngleIndex].fLastForce = angledata[iCurrentAngleIndex].shortShot.fForce + (angledata[iCurrentAngleIndex].LongShot.fForce - angledata[iCurrentAngleIndex].shortShot.fForce) / 2;
    }

    Owner->ChangeForce(angledata[iCurrentAngleIndex].fLastForce);
    Owner->iRotation = iMinAngle + iCurrentAngleIndex * ((iMaxAngle - iMinAngle) / iArraySize);

    if(Owner->proj)										// If there already is a projectile active
	{
		//Owner->proj->Destroy();							// then destroy it before creating a new one
		Owner->proj = NULL;
	}

    Owner->SpawnProjectile();
    iTries++;

    if(iTries > 10)
    {
        NextAngle();
        DecideNewForce();
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

    float ReCalcIndex = (float)iCurrentAngleIndex, ReSize = (float)iArraySize;

    // Adds a new point to the graph.
    graph->AddPoint(iCurrentAngleIndex, (angledata[iCurrentAngleIndex].fLastForce / fMaxForce), (ReCalcIndex / ReSize));

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
