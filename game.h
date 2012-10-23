#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include "math.h"

#include "vector2D.h"
#include "map.h"
#include "ai.h"
#include "projectile.h"
#include "catapult.h"
#include "particles.h"

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class MyGame
{
    public:
        static MyGame* Instance(void);  //Static instance to make the game available to all objects
        ~MyGame(void);

        static const int MAP_WIDTH = 1600, MAP_HEIGHT = 900;    // The size of the window
        static const int FPS = 60;  // The FPS which the game runs at

        void Run(int *argc, char** argv, int w, int h); // The initiation method
        void Update();              // Updates the objects
        void Draw();                // Draws all of the objects and such

        SDL_Surface* screen;        // The main screen everything is drawn to and then shown
        Vector2D vect;              // Saves the position of the base in order to create a catapult at that position
        Map* map;                   // The pointer to the current map.
        AI* ai;                     // The pointer to the current AI.

        bool bRunning;				// Is the game running or not?
        bool bDebug;				// Are we running in debug mode or not?
        Catapult catapult;			// The main cataput instance
        Particles* part;			// Random test particles

    private:
        static MyGame* m_instance;
        MyGame(void);

        int mx, my;					// Mouse X and Y pos (could be Vector2D?)
        Uint32 start;				// Stores the games current tick-rate in order to keep a stable frame-per-second rate.
        SDL_Event event;			// Handles SDL events eg. human input
};

#endif // GAME_H_INCLUDED
