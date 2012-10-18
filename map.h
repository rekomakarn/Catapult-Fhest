#include "SDL/SDL.h"
#include "vector2D.h"

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

class Map
{
    public:
        Map(SDL_Surface* screen, int SegmentCount);
        void GenerateMap(SDL_Surface* screen, int subSegments, int minHeight, int maxHeight, int diff, int seed);
        void GenerateMap(SDL_Surface* screen, int subSegments, int minHeight, int maxHeight, int diff);
        void DrawMap(bool debug);
        Vector2D GenerateBase(int baseEntry, int baseLength, bool bIsGoal);

        // Free Draw Functions, not needed but awesome
        void FreeDraw(float mx, float my);
        void FreeDrawBase(int baseEntry, int baseLength);

        // Undo support for draw
        void CreateUndoPoint(void);
        void RestoreUndoPoint(void);

        void SaveMap(void);

        // Behöver dessa public men bör nog vara funktioner för att hämta dem kanske
        int SegmentCount;
        Vector2D* Segments;
        Vector2D* UndoSegments;
        float SegmentDistance;

        Vector2D GoalIndexRange;

    private:
};

#endif // MAP_H_INCLUDED
