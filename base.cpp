#include "base.h"

Base::Base(float PosX, float PosY)
{
    fSize = 30;

    Position.x = PosX;
    Position.y = (PosY - fSize / 2);
}

void Base::Draw()
{
    glBegin(GL_QUADS);
    glColor4ub(0, 0, 255, 255);
    glVertex2i(Position.x + fSize / 2, Position.y - fSize / 2);
    glVertex2i(Position.x + fSize / 2, Position.y + fSize / 2);
    glVertex2i(Position.x - fSize / 2, Position.y + fSize / 2);
    glVertex2i(Position.x - fSize / 2, Position.y - fSize / 2);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor4ub(0, 0, 0, 255);
    glVertex2i(Position.x + fSize / 2, Position.y - fSize / 2);
    glVertex2i(Position.x + fSize / 2, Position.y + fSize / 2);
    glVertex2i(Position.x - fSize / 2, Position.y + fSize / 2);
    glVertex2i(Position.x - fSize / 2, Position.y - fSize / 2);
    glVertex2i(Position.x + fSize / 2, Position.y - fSize / 2);
    glEnd();
}
