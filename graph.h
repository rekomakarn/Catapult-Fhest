#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "Vector2D.h"
#include "ai.h"

class AI;

class Graph
{
    public:
        Graph();
        Graph(int arraysize, AI *ai);
        ~Graph();

        struct Point
        {
            Vector2D Position;
            bool bIsUsed;

            Point()
            {
                bIsUsed = false;
            }
        };

        float fSize;
        int iArraySize;
        AI *Owner;
        Point *Points;
        int iActivePoints;

        void Draw();
        void AddPoint(int index, float forcePrcnt, float anglePrcnt);
    private:
};

#endif // GRAPH_H_INCLUDED
