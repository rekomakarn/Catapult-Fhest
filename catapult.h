#ifndef CATAPULT_H_INCLUDED
#define CATAPULT_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include "vector2D.h"
#include "forcegauge.h"
#include "projectile.h"
#include "ai.h"

class Projectile;

class Catapult
{
    public:
        int iLength, iHeight;               // The size of the catapult.
        float fForce, fMaxForce;            // The current and maximum force at which the catapult launches the projectile.
        int iRotation;                      // The current rotation of the catapult

        Vector2D Position;					// Position of the cataoult model.
        ForceGauge forcegauge;              // The visual forcegauge of the catapult which represents the current force divided by the maximum force.
        Projectile* proj;					// The attached projectile, hopefully able to support more in the future.

        Catapult();                         // Constructor.
        void Update();                      // Updates the catapult and it's components.
        void Draw();                        // Draws the catapult and calls it's components draw-methods.

        void Rotate(int angle,bool CW);     // Changes the rotation of the catapult.
        void InitForceGauge();              // Initializes the forcegauge
        void ChangeForce(int f);            // Changes the force of the catapult.

        void SpawnProjectile();             // Spawns the projectile.

        AI* ai;                             // The catapult's AI.
};

#endif // CATAPULT_H_INCLUDED
