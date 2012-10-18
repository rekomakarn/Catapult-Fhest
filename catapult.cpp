#include "catapult.h"

Catapult::Catapult()
{
    Position.x = 0;
    Position.y = 0;
    iLength = 40;
    iHeight = 10;
}

void Catapult::InitForceGauge()
{
    // UHH OH MAGIC NUMBERS
    forcegauge.iWindowSize = 1600;
    forcegauge.SetSize(3);
    forcegauge.Position = Position + Vector2D(-20, -50);
    forcegauge.fCurrentForce = 50;
}

void Catapult::Rotate(bool CW)
{
    iRotation += CW ? 1 : -1;
}

void Catapult::Draw()
{
    forcegauge.Draw();

    Vector2D vect1 = Vector2D(-iLength / 2, -iHeight / 2);
    Vector2D vect2 = Vector2D(iLength / 2, -iHeight / 2);
    Vector2D vect3 = Vector2D(iLength / 2, iHeight / 2);
    Vector2D vect4 = Vector2D(-iLength / 2, iHeight / 2);

    vect1 = vect1.Rotate(iRotation) + Position + Vector2D(0, - iHeight / 2);
    vect2 = vect2.Rotate(iRotation) + Position + Vector2D(0, - iHeight / 2);
    vect3 = vect3.Rotate(iRotation) + Position + Vector2D(0, - iHeight / 2);
    vect4 = vect4.Rotate(iRotation) + Position + Vector2D(0, - iHeight / 2);

    glBegin(GL_QUADS);
    glColor4ub(90, 90, 90, 255);
    glVertex2i(vect1.x, vect1.y);
    glVertex2i(vect2.x, vect2.y);
    glVertex2i(vect3.x, vect3.y);
    glVertex2i(vect4.x, vect4.y);
    glEnd();

    glColor4ub(0, 0, 0, 255);
    glBegin(GL_LINE_STRIP);
    glVertex2i(vect1.x, vect1.y);
    glVertex2i(vect2.x, vect2.y);
    glVertex2i(vect3.x, vect3.y);
    glVertex2i(vect4.x, vect4.y);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor4ub(185, 122, 87, 255);
    glVertex2i(Position.x - 10, Position.y);
    glVertex2i(Position.x, Position.y - 20);
    glVertex2i(Position.x + 10, Position.y);
    glEnd();

    glColor4ub(0, 0, 0, 255);
    glBegin(GL_LINE_STRIP);
    glVertex2i(Position.x - 10, Position.y);
    glVertex2i(Position.x, Position.y - 20);
    glVertex2i(Position.x + 10, Position.y);
    glEnd();
}
