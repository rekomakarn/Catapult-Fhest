#include "vector2D.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "forcegauge.h"
#include <iostream>

#ifndef CATAPULT_H_INCLUDED
#define CATAPULT_H_INCLUDED

class Catapult
{
    public:
        int iLength, iHeight, iRotation;
        Vector2D Position;
        Catapult();
        void Draw();
        void Rotate(bool CW);
        ForceGauge forcegauge;
        void InitForceGauge();
    private:
};

#endif // CATAPULT_H_INCLUDED
