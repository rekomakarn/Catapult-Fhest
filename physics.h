#include "vector2D.h"
#include <cstddef>

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

class Physics
{
    public:
        // Det va const som �r lite konstigt syntax, d�rf�r du fick status 3
        const static float GRAVITY, TERMINAL_VELOCITY, AIR_RES;

        // Class related function
        static Physics* Instance();     // Calling the instance

        void ApplyGravity(Vector2D &obj);

    private:
        // Class related function
        Physics(void);                  // Private constructor
        static Physics* pInstance;      // The instance
};

#endif // PHYSICS_H_INCLUDED
