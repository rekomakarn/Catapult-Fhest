#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include "math.h"

#include "vector2D.h"

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

class Game;

class Map
{
    public:
        Map(SDL_Surface* screen, int SegmentCount, Vector2D WinSize);       // Constructor

        void GenerateMap(SDL_Surface* screen, int subSegments, int minHeight, int maxHeight, int diff, int seed);   // Generates the map according to a specific random seed.
        void GenerateMap(SDL_Surface* screen, int subSegments, int minHeight, int maxHeight, int diff);             // Generates the map according to a random random seed.

        void DrawMap(bool debug);             // Draws the map.

        Vector2D GenerateBase(int baseEntry, int baseLength, bool bIsGoal); // Generates two bases on the map.

        // Free Draw Functions, not needed but awesome
        void FreeDraw(float mx, float my);
        void FreeDrawBase(int baseEntry, int baseLength);

        // Undo support for draw
        void CreateUndoPoint(void);
        void RestoreUndoPoint(void);

        void SaveMap(void);

        int SegmentCount;                   // The amount of segments the map is made up from.
        Vector2D* Segments;                 // The actual segments.
        Vector2D* UndoSegments;
        float SegmentDistance;              // The distance between each segment.

        Vector2D GoalIndexRange;

    private:
    //Replace with something good...
        Vector2D WindowSize;
};

#endif // MAP_H_INCLUDED
