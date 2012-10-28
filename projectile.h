#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include "math.h"
#include "vector2D.h"
#include "physics.h"
#include "map.h"
#include "physics.h"
#include "collisiondata.h"
#include "game.h"

class Projectile
{
    public:
        int iRotation, iRotationSpeed;              // The speed at which the projectile rotates.
        float fMass;                                // The mass of the projectile. Currently not used.
        float fSize;                                // The visual size of the projectile.
        Vector2D Position;                          // The current position of the projectile.
        Vector2D MoveVector;                        // The current force the projectile has.
        bool bCollisionActive;                      // Is the projectile active, or should it be destroyed?

        Projectile();                               // Constructor.
        ~Projectile();                              // Destructor.
        Projectile(Vector2D &vect, Vector2D &force);// Main constructor.

        void Update();                              // Updates the projectile and it's components.
        void CheckCollision();                      // Checks for collision.
        void Draw();                                // Draws the projectile onto the screen
        void Destroy();                             // Calls the destructor.

        int iLineIndex, iLineAmount;                // Sets the amount of lines, as well as which one to draw next.
        Vector2D* LinePoints;                       // Saves the points between which the lines are drawn.

        CollisionData *colData;                     // The object where the collisions data is stored.
};

#endif // PROJECTILE_H_INCLUDED
