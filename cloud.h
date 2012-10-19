#include "vector2D.h"
#include "SDL/SDL_opengl.h"

#ifndef CLOUD_H_INCLUDED
#define CLOUD_H_INCLUDED

class Cloud
{
    public:
        Vector2D Position;
        Cloud();
        Cloud(Vector2D pos);
        void Update();
        void Draw();
    private:

};

#endif // CLOUD_H_INCLUDED
