#include "vector2D.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "forcegauge.h"
#include <iostream>
#include "projectile.h"
#include "ai.h"

#ifndef CATAPULT_H_INCLUDED
#define CATAPULT_H_INCLUDED

class Catapult
{
    public:
        int iLength, iHeight;
        float fForce, fMaxForce;
        int iRotation;

        Vector2D Position;					// Position of the cataoult model
        ForceGauge forcegauge;
        Projectile* proj;					// The attached projectile, hopefully able to support more in the future

        Catapult();
        void Update();
        void Draw();

        void Rotate(bool CW);
        void InitForceGauge();
        void ChangeForce(int f);

        void SpawnProjectile();
};

#endif // CATAPULT_H_INCLUDED
