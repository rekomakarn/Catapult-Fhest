#include "drawing.h"
#include <cstddef>                              // GCC don't know bout my NULL constants!

#include "SDL/SDL.h"
// #include "SDL/SDL_image.h"

#include "math.h"

#include "vector2D.h"

Drawing* Drawing::pInstance = NULL;

Drawing::Drawing(void)
{
    return;
}

Drawing* Drawing::Instance()
{
    return pInstance;
}

// Adapterats från http://en.wikipedia.org/wiki/Bresenham's_line_algorithm under "The algorithm" och simplification
void Drawing::DrawLine(SDL_Surface* screen, Vector2D* position1, Vector2D* position2)
{
    int sx, sy;
    float error, error2;
    int DeltaX = abs(position2->x - position1->x);
    int DeltaY = abs(position2->y - position1->y);

    sx = position1->x < position2->x ? 1 : -1;
    sy = position1->y < position2->y ? 1 : -1;
    error = (float)DeltaX - (float)DeltaY;

    while(position1->x != position2->x && position1->y != position2->y)
    {
        //DrawPixel(screen, position1);
        Drawing::Instance()->DrawPixel(screen, position1->x, position1->y,  SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));
        error2 = error * 2;

        if(error2 > -DeltaY)
        {
            error -= DeltaY;
            position1->x += sx;
        }

        if(error2 < DeltaX)
        {
            error += DeltaX;
            position1->y += sy;
        }
    }
}

void Drawing::DrawPixel(SDL_Surface* screen, int x, int y, Uint32 color)
{
    unsigned int *ptr = (unsigned int*)screen->pixels;
    int lineoffset = y * (screen->pitch / 4);
    ptr[lineoffset + x] = color;
}

void Drawing::DrawPixel(SDL_Surface* screen, Vector2D* position)
{
    unsigned int *ptr = (unsigned int*)screen->pixels;
    int lineoffset = (int)position->y * (screen->pitch / 4);
    ptr[lineoffset + (int)position->x] = SDL_MapRGB(screen->format, 0xff, 0xff, 0xff);
}
