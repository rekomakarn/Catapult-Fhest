#include "vector2D.h"
#include "SDL/SDL_opengl.h"

#ifndef FORCEGAUGE_H_INCLUDED
#define FORCEGAUGE_H_INCLUDED

class ForceGauge
{
    public:
        float fCurrentForce;
        float fGaugeSize;
        Vector2D Position;
        int iWindowSize;

        ForceGauge();
        ForceGauge(int size);

        void Draw();
        void Update();
        void SetCurrentForce(float force);
        void SetSize();
        void SetSize(int size);
    private:

};

#endif // FORCEGAUGE_H_INCLUDED
