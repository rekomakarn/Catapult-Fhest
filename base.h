#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include "vector2D.h"
#include "SDL/SDL_opengl.h"

class Base
{
    public:
        Base(Vector2D Pos);
        Base(float PosX, float PosY);

        Vector2D Position;
        float fSize;

        void Draw();
    private:

};

#endif // BASE_H_INCLUDED
