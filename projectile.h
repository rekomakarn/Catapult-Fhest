#include "vector2D.h"
#include "physics.h"
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "map.h"
#include "physics.h"
#include "math.h"

#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

class Projectile
{
    public:
        int iRotation;
        float fMass;
        float fSize;
        Vector2D Position;
        Vector2D MoveVector;
        bool bCollisionActive;

        Projectile();
        ~Projectile();                                      // Destructor
        Projectile(float x, float y);
        Projectile(Vector2D &vect, Vector2D &force);
        Projectile(float mass);
        Projectile(float x, float y, float mass);

        void Update();
        void CheckCollision();
        void Draw();
        void Destroy();
};

#endif // PROJECTILE_H_INCLUDED
