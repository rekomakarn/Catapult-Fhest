#include "map.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include "vector2D.h"
#include "SDL/SDL.h"
#include "drawing.h"
#include <time.h>
#include "game.h"

Map::Map(SDL_Surface* screen, int SegmentCount)
{
    Map::GenerateMap(screen, SegmentCount, MyGame::MAP_HEIGHT, MyGame::MAP_HEIGHT / 2, 20);
    GoalIndexRange = Vector2D(0,0);
}

void Map::GenerateMap(SDL_Surface* screen, int subSegments, int minHeight, int maxHeight, int diff, int seed)
{
    diff = diff > 100 ? 100 : diff;
    diff = diff == 0 ? 1 : diff;

    int SegmentCount = pow(2, subSegments) + 1;
    float SegmentDistance = (float)MyGame::MAP_WIDTH / ((float)SegmentCount - 1);
    // Kom precis på en sak här: +1 sen -1.. hm.. vågar inte ändra nu dock
    // för då kommer allt säkert dö :P

    Vector2D* segments = new Vector2D[SegmentCount];

    std::cout << "Seed: " << seed << std::endl;
    std::cout << "SegmentDistance: " << SegmentDistance << std::endl;
    std::cout << "SegmentCount: " << SegmentCount << std::endl;
    std::cout << std::endl;

    srand(seed);

    for(int i = 0; i < SegmentCount; i++)
    {
        int xPos = i * SegmentDistance;
        int yDiff = 0;

        if(i == SegmentCount - 1)
            xPos = MyGame::MAP_WIDTH - 1;

        segments[i].x = xPos;

        if(i == 0)
            segments[i].y = minHeight - (minHeight - maxHeight) / 2; // rand()% minHeight, maxHeight;
        else
        {
            segments[i].y = segments[i - 1].y;
            // Makes sure the next y-position is within the limits.
            int tries = 0;
            do
            {
                ++tries;

                yDiff = rand() % diff;
                yDiff -= (diff / 2);

                //std::cout << "yDiff = " << yDiff << "\t\t x = " << xPos << std::endl;
                //std::cout << "while(" << segments[i].y + yDiff << ") < " << maxHeight << " || (" << segments[i].y + yDiff << ") > " << minHeight << ")" << std::endl;

            }
            while((segments[i].y + yDiff) <= maxHeight || (segments[i].y + yDiff) >= minHeight);

            //std::cout << "#" << i << "# Took: -" << tries << "- tries" << std::endl;

            segments[i].y += yDiff;
        }
    }

    this->Segments = segments;
    this->SegmentCount = SegmentCount;
    this->SegmentDistance = SegmentDistance;
}

void Map::GenerateMap(SDL_Surface* screen, int subSegments, int minHeight, int maxHeight, int diff)
{
    Map::GenerateMap(screen, subSegments, minHeight, maxHeight, diff, time(NULL));
}

void Map::DrawMap(bool debug)
{
    for(int i = 0; i < SegmentCount; i++)
    {
        if(!debug && i > 0)
        {
            if(i % 2 == 1)
                glColor4ub(0, 255, 0, 255);
            else
                glColor4ub(0, 200, 0, 255);
            //glVertex2i(Segments[i].x, Segments[i].y);
            glBegin(GL_QUADS);
            glVertex2i(Segments[i - 1].x, Segments[i - 1].y);
            glVertex2i(Segments[i].x, Segments[i].y);
            glVertex2i(Segments[i].x, MyGame::MAP_HEIGHT);
            glVertex2i(Segments[i - 1].x, MyGame::MAP_HEIGHT);
            glEnd();
        }

        else if(i > 0)
        {
            if(i % 2 == 1)
                glColor4ub(0, 255, 0, 255);
            else
                glColor4ub(255, 0, 0, 255);
            glBegin(GL_LINES);
            glVertex2i(Segments[i - 1].x, Segments[i - 1].y);
            glVertex2i(Segments[i].x, Segments[i].y);
            glEnd();
        }
    }

    glColor4ub(0, 0, 0, 255);
    glBegin(GL_LINE_STRIP);
    for(int i = 1; i < SegmentCount; i++)
    {
        glVertex2i(Segments[i - 1].x, Segments[i - 1].y);
        glVertex2i(Segments[i].x, Segments[i].y);
    }
    glEnd();
}

Vector2D Map::GenerateBase(int baseEntry, int baseLength, bool bIsGoal)
{
    Vector2D vect;
    // Force minimum and maximum length so we don't get index errors
    baseLength = baseLength < 6 ? 6 : baseLength;
    baseLength = baseLength > MyGame::MAP_WIDTH - baseLength ? MyGame::MAP_WIDTH - baseLength : baseLength;

    int averageHeight = 0;
    for(int i = baseEntry; i < baseEntry+baseLength; i++)
    {
        averageHeight += this->Segments[baseEntry].y;
    }
    averageHeight = averageHeight / baseLength;

    int segmentInterval = (int)baseLength / 6;
    for(int i = baseEntry; i < baseEntry+baseLength; i++)
    {
        if(i < baseEntry + segmentInterval)
            this->Segments[i].y = averageHeight + segmentInterval - (i - baseEntry);
        else if(i >= baseEntry + baseLength - segmentInterval)
            this->Segments[i].y = averageHeight + segmentInterval + (i-(baseEntry+baseLength));
        else
            this->Segments[i].y = averageHeight;
    }

    vect = Segments[(baseEntry+baseLength) / 2];

    if(bIsGoal)
    {
        GoalIndexRange = Vector2D(baseEntry, baseEntry + baseLength);
    }

    return vect;
}

void Map::FreeDraw(float mx, float my)
{
    for(int i = 0; i < SegmentCount; i++)
    {
        if(Segments[i].x == mx)
        {
            Segments[i].y = my;
            if(i > 0)
                Segments[i-1].y -= (Segments[i-1].y - Segments[i].y) * 0.6f;
            if(i > 1)
                Segments[i-2].y -= (Segments[i-2].y - Segments[i-1].y) * 0.3f;
            if(i < SegmentCount)
                Segments[i+1].y -= (Segments[i+1].y - Segments[i].y) * 0.6f;
            if(i < SegmentCount-1)
                Segments[i+1].y -= (Segments[i+1].y - Segments[i].y) * 0.3f;
        }
    }
}

void Map::CreateUndoPoint(void)
{
    std::cout << std::endl << "Created Unto!";
    //this->UndoSegments = this->Segments;
}

void Map::RestoreUndoPoint(void)
{
    std::cout << std::endl << "Restored Undo!";
    //this->Segments = this->UndoSegments;
}

void Map::FreeDrawBase(int baseEntry, int baseLength)
{
    Map::GenerateBase(baseEntry, baseLength, false);
}

void Map::SaveMap(void)
{
}
