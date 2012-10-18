#include "vector2D.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "forcegauge.h"
#include <iostream>
#include "projectile.h"

#ifndef CATAPULT_H_INCLUDED
#define CATAPULT_H_INCLUDED

class Catapult
{
    public:
        int iLength, iHeight, iRotation;
        int iForce, iMaxForce;
        Vector2D Position;
        Catapult();
        void Draw();
        void Rotate(bool CW);
        ForceGauge forcegauge;
        void InitForceGauge();
        void Update();
        void ChangeForce(int f);

        Projectile* proj;
        void SpawnProjectile();
        void DrawProjectile();
    private:
};

#endif // CATAPULT_H_INCLUDED
