#include "projectile.h"
#include "game.h"

Projectile::Projectile()
{
    bCollisionActive = true;
    fMass = 10;
    fSize = 10;
    MoveVector.x = 11;
    MoveVector.y = -10;
}

Projectile::~Projectile()
{
    // <Particle Explosion here mofo!>

    MyGame::Instance()->proj = new Projectile(MyGame::Instance()->vect, MyGame::Instance()->ai->currentForce);
}

Projectile::Projectile(float x, float y)
{
    bCollisionActive = true;
    fMass = 10;
    fSize = 10;
    Position.x = x;
    Position.y = y;
    MoveVector.x = 5;
    MoveVector.y = -10;
}

Projectile::Projectile(Vector2D &vect, Vector2D &force)
{
    bCollisionActive = true;
    fMass = 10;
    fSize = 10;
    Position = vect;
    MoveVector.x = force.x;
    MoveVector.y = force.y;
}

Projectile::Projectile(float mass)
{
    bCollisionActive = true;
    fMass = mass;
}

Projectile::Projectile(float x, float y, float mass)
{
    bCollisionActive = true;
    fMass = mass;
    Position.x = x;
    Position.y = y;
}

void Projectile::UpdatePosition()
{
    Physics::Instance()->ApplyGravity(MoveVector);

    iRotation++;
    if(iRotation > 360)
        iRotation = 0;

    Position.x += MoveVector.x;//  += MoveVector;
    Position.y += MoveVector.y;

    CheckCollision();
}

// Borde vara i physics klassen men lägger den här så länge
void Projectile::CheckCollision()
{
    // [!] Detta är bara en test, den kommer bara kollidera med de exakta punkterna och inte
    // med edge/line imellan två punkter, funkar bör den dock typ..
    Vector2D* segments = MyGame::Instance()->map->Segments;
    float segmentDistance = MyGame::Instance()->map->SegmentDistance;

    if(bCollisionActive)
    {
        // Derp level LA. Riots incoming
        int indexPos = ceilf(Position.x / segmentDistance);

        if(Position.y >= segments[indexPos].y && Position.x + 3 >= segments[indexPos].x && Position.x - 3 <= segments[indexPos].x) // Missed target, hit gound
        {
            std::cout << "HIT! index=" << indexPos << "\t x=" << segments[indexPos].x << "\t y="<< segments[indexPos].y << "!" << std::endl;
            MyGame::Instance()->ai->DecideNewForce(indexPos, Vector2D(segments[indexPos].x, segments[indexPos].y));
            bCollisionActive = false;
        }
        else if(Position.y) // Out of bounds horizontally
        {
        }
    }
}

void Projectile::Draw()
{
    if(bCollisionActive)
    {
        glBegin(GL_QUADS);
        glColor4ub(255, 0, 0, 255);

        Vector2D vect1 = Vector2D((0 - fSize / 2), (0 - fSize / 2));
        Vector2D vect2 = Vector2D((0 + fSize / 2), (0 - fSize / 2));
        Vector2D vect3 = Vector2D((0 + fSize / 2), (0 + fSize / 2));
        Vector2D vect4 = Vector2D((0 - fSize / 2), (0 + fSize / 2));

        vect1 = vect1.Rotate(iRotation) + Position;
        vect2 = vect2.Rotate(iRotation) + Position;
        vect3 = vect3.Rotate(iRotation) + Position;
        vect4 = vect4.Rotate(iRotation) + Position;

        glVertex2i(vect1.x, vect1.y);
        glVertex2i(vect2.x, vect2.y);
        glVertex2i(vect3.x, vect3.y);
        glVertex2i(vect4.x, vect4.y);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor4ub(0, 0, 0, 255);
        glVertex2i(vect1.x, vect1.y);
        glVertex2i(vect2.x, vect2.y);
        glVertex2i(vect3.x, vect3.y);
        glVertex2i(vect4.x, vect4.y);
        glEnd();
    }

}

void Projectile::Destroy()
{
    delete this;
}
