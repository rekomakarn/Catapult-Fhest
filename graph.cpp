#include "graph.h"
#include <iostream>
Graph::Graph()
{

}

Graph::Graph(int arraysize, AI *ai)
{
    iArraySize = arraysize;
    Owner = ai;
    Points = new Point[iArraySize];
    iActivePoints = 0;
    fSize = 400;
}

Graph::~Graph()
{

}

void Graph::AddPoint(int index, float forcePrcnt, float anglePrcnt)
{
    Points[index].Position.y = forcePrcnt;
    Points[index].Position.x = anglePrcnt;
    Points[index].bIsUsed = true;
    iActivePoints++;
}

void Graph::Draw()
{
    // Background of graph
    glBegin(GL_QUADS);
    glColor4ub(255, 255, 255, 255);
    glVertex2i(50, 50);
    glVertex2i(50 + fSize, 50);
    glVertex2i(50 + fSize, 50 + fSize);
    glVertex2i(50, 50 + fSize);
    glEnd();

    // Outline around the graph
    glBegin(GL_LINE_STRIP);
    glColor4ub(0, 0, 0, 255);
    glVertex2i(50, 50);
    glVertex2i(50 + fSize, 50);
    glVertex2i(50 + fSize, 50 + fSize);
    glVertex2i(50, 50 + fSize);
    glVertex2i(50, 50);
    glEnd();

    if(iActivePoints >= 2)
    {
        // Lines connecting the points
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i <= iArraySize; i++)
        {
            if(Points[i].bIsUsed)
            {
                glColor4ub(0, 0, 0, 255);
                glVertex2i(50 + Points[i].Position.x * fSize, 50 + fSize - Points[i].Position.y * fSize);
            }
        }
        glEnd();

        // Lines marking the sections
        glBegin(GL_LINES);
        if(iActivePoints >= 2)
        {
            for(int i = 0; i <= iArraySize; i++)
            {
                if(Points[i].bIsUsed && i != 0 && i != iArraySize)
                {
                    glColor4ub(255, 0, 0, 255);
                    glVertex2i(50 + Points[i].Position.x * fSize, 50);
                    glVertex2i(50 + Points[i].Position.x * fSize, 50 + fSize);
                }
            }
        }
        glEnd();
    }
}
