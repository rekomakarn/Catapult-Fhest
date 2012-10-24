#ifndef PARTICLES_H_INCLUDED
#define PARTICLES_H_INCLUDED

#include "vector2D.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>

class Particles
{
    public:
        // Public Functions
        Particles();                        // Default Constructor
        ~Particles();                       // Destructor
        Particles(Vector2D origin);         // Constructor with origin
        void Update();                      // Update Function
        void Draw();                        // Draw Function

    private:
};

#endif // PARTICLES_H_INCLUDED
