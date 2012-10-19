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
    iRotationSpeed = force.x / 2;
    iLineAmount = 1;
    iLineIndex = 1;
    LinePoints = new Vector2D[100];
    LinePoints[0] = Position;
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

void Projectile::Update()
{
    Physics::Instance()->ApplyGravity(MoveVector);

    iRotation += iRotationSpeed;
    if(iRotation > 360)
        iRotation = 0;

    Position.x += MoveVector.x;//  += MoveVector;
    Position.y += MoveVector.y;

    iLineIndex++;
    if(iLineIndex > 2)
    {
        LinePoints[iLineAmount] = Position;
        iLineAmount++;
        iLineIndex = 0;
    }

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

        if(Position.y >= segments[indexPos].y && Position.x + 5 >= segments[indexPos].x && Position.x - 5 <= segments[indexPos].x) // Missed target, hit gound
        {
            std::cout << "Projectile::CheckCollision(): HIT! index=" << indexPos << "\t x=" << segments[indexPos].x << "\t y="<< segments[indexPos].y << "!" << std::endl;
            //MyGame::Instance()->ai->DecideNewForce(indexPos, Vector2D(segments[indexPos].x, segments[indexPos].y));
            bCollisionActive = false;
        }
        else if(Position.x > MyGame::MAP_WIDTH)
        {
            std::cout << "Projectile::CheckCollision(): Projectile went outside the map to the right!" << std::endl;
            //MyGame::Instance()->ai->DecideNewForce(indexPos, Vector2D(segments[indexPos].x, segments[indexPos].y));
            bCollisionActive = false;
        }
        else if(Position.x < 0)
        {
            std::cout <<"Projectile::CheckCollision(): Projectile went outside the map to the left!" << std::endl;
            bCollisionActive = false;
        }
        else if(Position.y) // Out of bounds horizontally
        {
        }
    }
}

void Projectile::Draw()
{
    for(int i = 1; i < iLineAmount; i++)
    {
        if(i % 2)
        {
            glBegin(GL_LINES);
            glColor4ub(255, 255, 255, 255);
            glVertex2i(LinePoints[i].x, LinePoints[i].y);
            glVertex2i(LinePoints[i - 1].x, LinePoints[i - 1].y);
            glEnd();
        }

    }

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
