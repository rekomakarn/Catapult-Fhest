#include "vector2D.h"

#ifndef COLLISIONDATA_H_INCLUDED
#define COLLISIONDATA_H_INCLUDED

class CollisionData
{
    public:
        enum CollisionType {Short, Long, OutMapFar, OutMapShort};
        CollisionType colType;

        CollisionData(Vector2D force, Vector2D position);
        ~CollisionData();

        Vector2D Force;
        Vector2D Position;
    private:

};

#endif // COLLISIONDATA_H_INCLUDED
