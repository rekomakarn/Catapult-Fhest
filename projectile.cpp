#include "projectile.h"

Projectile::Projectile()
{

}

Projectile::~Projectile()
{

}

Projectile::Projectile(Vector2D &vect, Vector2D &force)
{
    // This decides if the projectile is active and should not be destroyed.
    bCollisionActive = true;

    // Sets the mass of the projectile, has no effect at the moment.
    fMass = 10;

    // Decides the size of the projectile visually.
    fSize = 10;

    // Sets the position of the projectile. Most often it is set to the position of the catapult.
    Position = vect;

    // Sets the force to the calculated amount.
    MoveVector.x = force.x;
    MoveVector.y = force.y;

    // Rotationspeed is set by using semi-magic numbers.
    iRotationSpeed = force.x / 2;

    // Initiates the drawing of lines behind the projectile.
    iLineAmount = 1;
    iLineIndex = 1;
    LinePoints = new Vector2D[100];
    LinePoints[0] = Position;

    // Initializes the collisiondata.
    colData = NULL;
}

void Projectile::Update()
{
    // Applies gravity to the projectile according to the strength set in the physics class
    Physics::Instance()->ApplyGravity(MoveVector);

    // Sets the current rotation of the projectile.
    iRotation += iRotationSpeed;
    if(iRotation > 360)
        iRotation = 0;

    // Moves the projectile according to it's force.
    Position = Position + MoveVector;

    // Creates the positions between which the lines are drawn and stores them
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
    Vector2D* segments = MyGame::Instance()->map->Segments;
    float segmentDistance = MyGame::Instance()->map->SegmentDistance;

    if(bCollisionActive)
    {
        int indexPos = ceilf(Position.x / segmentDistance);

        // Projectile collides with ground.
        if(Position.y >= segments[indexPos].y && Position.x + 5 >= segments[indexPos].x && Position.x - 5 <= segments[indexPos].x) // Missed target, hit gound
        {
            // Creates new collision data for when the projectile hits the ground.
            colData = new CollisionData(MoveVector, Position);

            // Stub for long shot
//            colData.colType = Position.x < 5 /* Base's x-position */ ? CollisionData.CollisionType.Short : CollisionData.CollisionType.Long;

            std::cout << "Projectile::CheckCollision(): HIT! index=" << indexPos << "\t x=" << segments[indexPos].x << "\t y="<< segments[indexPos].y << "!" << std::endl;
            bCollisionActive = false;
        }

        // Projectile goes outside the window to the right.
        else if(Position.x > MyGame::MAP_WIDTH)
        {
            std::cout << "Projectile::CheckCollision(): Projectile went outside the map to the right!" << std::endl;
            bCollisionActive = false;
        }

        // Projectile goes outside the window to the left.
        else if(Position.x < 0)
        {
            std::cout <<"Projectile::CheckCollision(): Projectile went outside the map to the left!" << std::endl;
            bCollisionActive = false;
        }
    }
}

void Projectile::Draw()
{
    // Draws the lines behind the projectile.
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

    // Draws the projectile.
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
