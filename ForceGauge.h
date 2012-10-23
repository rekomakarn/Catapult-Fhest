#include "vector2D.h"
#include "SDL/SDL_opengl.h"

#ifndef FORCEGAUGE_H_INCLUDED
#define FORCEGAUGE_H_INCLUDED

class ForceGauge
{
    public:
        float fCurrentForce;                // The current force which the forcegauge corresponds to.
        float fGaugeSize;                   // The visual size of the gauge.
        Vector2D Position;                  // The position of the forcegauge.
        int iWindowSize;                    // The width of the screen.

        ForceGauge();                       // Constructor.
        ForceGauge(int size);               // Constructor.

        void Draw();                        // Draws the forcegauge onto the screen.
        void Update();                      // Updates the forcegauge and it's components.
        void SetCurrentForce(float force);  // Sets the current force of the forcegauge.
        void SetSize();                     // Sets the size of the forcegauge to a default value.
        void SetSize(int size);             // Sets the size of the forcegauge to a specified value.
    private:

};

#endif // FORCEGAUGE_H_INCLUDED
