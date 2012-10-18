#include "SDL/SDL.h"
#include "vector2D.h"

#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED
// #include "SDL/SDL_image.h"

class Drawing
{
    public:
        // Class related function
        static Drawing* Instance();     // Calling the instance

        // Drawing library itself
       //  void DrawLine(SDL_Surface*, int x0, int x1, int y0, int y1);
        void DrawLine(SDL_Surface* screen, Vector2D* position1, Vector2D* position2);
        void DrawPixel(SDL_Surface*, int x, int y, Uint32 color);
        void DrawPixel(SDL_Surface* screen, Vector2D* position);

    private:
        // Class related function
        Drawing(void);                  // Private constructor
        static Drawing* pInstance;      // The instance

        // Drawing library itself
};

#endif // DRAWING_H_INCLUDED
