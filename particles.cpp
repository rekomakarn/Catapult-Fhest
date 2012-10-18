#include "particles.h"

Particles::Particles()
{

}

Particles::~Particles()
{

}

Particles::Particles(Vector2D origin)
{

}

void Particles::Update()
{
    Draw();                     // Self calling draw for now
}

void Particles::Draw()
{
    glBegin(GL_QUADS);
    glColor4ub(128, 64, 64, 255);

    Vector2D vect1 = Vector2D(5, 5);
    Vector2D vect2 = Vector2D(10, 5);
    Vector2D vect3 = Vector2D(10, 10);
    Vector2D vect4 = Vector2D(5, 10);

    glVertex2i(vect1.x, vect1.y);
    glVertex2i(vect2.x, vect2.y);
    glVertex2i(vect3.x, vect3.y);
    glVertex2i(vect4.x, vect4.y);
    glEnd();
}
