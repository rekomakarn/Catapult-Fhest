#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "vector2D.h"
#include "map.h"
#include "ai.h"
#include "projectile.h"
#include "catapult.h"
#include "particles.h"
#include <iostream>
#include "math.h"

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class MyGame
{
    public:
        static MyGame* Instance(void);
        ~MyGame(void);
        static const int MAP_WIDTH = 1600, MAP_HEIGHT = 900;
        static const int FPS = 60;
        void SwapValues(int &a, int &b);
        void SwapCoordinates(Vector2D &obj);
        void DrawPixel(SDL_Surface* screen, int x, int y);
        void DrawPixel(SDL_Surface* screen, Vector2D* position);
        void DrawLine(SDL_Surface* screen, Vector2D* position1, Vector2D* position2);
        void DrawLine(SDL_Surface* screen, Vector2D& position1, Vector2D& position2);
        void DrawMap(SDL_Surface* screen, int minHeight, int maxHeight, int minDiff, int maxDiff, int Segments);
        void DrawMap(SDL_Surface* screen, Vector2D* Segments);
        void Run(int *argc, char** argv, int w, int h);
        void Update();  // Added this and Draw() to get a better flow
        void Draw();

        SDL_Surface* screen;		// The main screen everything is drawn to and then shown
        Vector2D vect;
        Map* map;
        AI* ai;
        Projectile* proj;

        bool bRunning;				// Is the game running or not?
        bool bDebug;				// Are we running in debug mode or not?

        Particles* part;			// Random test particles

    private:
        static MyGame* m_instance;
        MyGame(void);

        int mx, my;					// Mouse X and Y pos (could be Vector2D?)
        Catapult catapult;			// The main cataput instance
        Uint32 start;				// Idontknowactually
};

#endif // GAME_H_INCLUDED
