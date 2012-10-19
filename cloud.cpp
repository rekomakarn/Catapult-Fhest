#include "cloud.h"

Cloud::Cloud()
{

}

Cloud::Cloud(Vector2D pos)
{
    Position = pos;
}

void Cloud::Update()
{
    Position.x += 0.3f;
}

void Cloud::Draw()
{
    glBegin(GL_QUADS);
    glColor4ub(235, 235, 255, 255);
    glVertex2i(Position.x  - 70, Position.y);
    glVertex2i(Position.x - 70, Position.y - 28);
    glVertex2i(Position.x + 70, Position.y - 28);
    glVertex2i(Position.x + 70, Position.y);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(Position.x - 49, Position.y - 28);
    glVertex2i(Position.x - 49, Position.y - 49);
    glVertex2i(Position.x - 21, Position.y - 49);
    glVertex2i(Position.x - 21, Position.y - 28);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(Position.x - 21, Position.y - 28);
    glVertex2i(Position.x - 21, Position.y - 63);
    glVertex2i(Position.x + 21, Position.y - 63);
    glVertex2i(Position.x + 21, Position.y - 28);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(Position.x + 21, Position.y - 28);
    glVertex2i(Position.x + 21, Position.y - 42);
    glVertex2i(Position.x + 42, Position.y - 42);
    glVertex2i(Position.x + 42, Position.y - 28);
    glEnd();
}
