#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

#include "vector2D.h"
#include <cstddef>

class Physics
{
    public:
        const static float GRAVITY, TERMINAL_VELOCITY, AIR_RES; // Sets the core physics values.

        // Class related function
        static Physics* Instance();         // Calling the instance

        void ApplyGravity(Vector2D &obj);   // Applies gravity to a vector.

    private:
        // Class related function
        Physics(void);                      // Private constructor
        static Physics* pInstance;          // The instance
};

#endif // PHYSICS_H_INCLUDED
