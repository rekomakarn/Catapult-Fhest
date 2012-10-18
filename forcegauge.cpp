#include "forcegauge.h"

ForceGauge::ForceGauge()
{
    SetSize();
    Position = Vector2D(100, 100);
}

ForceGauge::ForceGauge(int size)
{
    SetSize();
    Position = Vector2D(100, 100);
}

void ForceGauge::SetSize()
{
    fGaugeSize = ((iWindowSize / 100) * 50);
}

void ForceGauge::SetSize(int size)
{
    fGaugeSize = ((iWindowSize / 100) * size);
}

void ForceGauge::SetCurrentForce(int force)
{
    force = force > 100 ? 100 : force;
    force = force < 0 ? 0 : force;

    fCurrentForce = force;
}

void ForceGauge::Draw()
{
    glBegin(GL_QUADS);
    glColor4ub(0, 255, 0, 255);
    glVertex2i(Position.x, Position.y);
    glVertex2i(Position.x, Position.y + fGaugeSize / 5);
    glVertex2i(Position.x + (fGaugeSize  / 100) * fCurrentForce, Position.y + fGaugeSize / 5);
    glVertex2i(Position.x + (fGaugeSize / 100) * fCurrentForce, Position.y);
    glEnd();

    glBegin(GL_QUADS);
    glColor4ub(255, 0, 0, 255);
    glVertex2i(Position.x + (fGaugeSize / 100) * fCurrentForce, Position.y);
    glVertex2i(Position.x + (fGaugeSize / 100) * fCurrentForce, Position.y + fGaugeSize / 5);
    glVertex2i(Position.x + fGaugeSize, Position.y + fGaugeSize / 5);
    glVertex2i(Position.x + fGaugeSize, Position.y);
    glEnd();

    glColor4ub(0, 0, 0, 255);
    glBegin(GL_LINE_STRIP);
    glVertex2i(Position.x, Position.y);
    glVertex2i(Position.x + fGaugeSize, Position.y);
    glVertex2i(Position.x + fGaugeSize, Position.y + fGaugeSize / 5);
    glVertex2i(Position.x, Position.y + fGaugeSize / 5);
    glVertex2i(Position.x, Position.y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(Position.x + (fGaugeSize / 100) * fCurrentForce, Position.y);
    glVertex2i(Position.x + (fGaugeSize / 100) * fCurrentForce, Position.y + fGaugeSize / 5);
    glEnd();
}
