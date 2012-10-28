#include "catapult.h"

Catapult::Catapult()
{
    Position.x = 0;
    Position.y = 0;

    iLength = 40;
    iHeight = 10;

    proj = NULL;

    // Sets the defualt rotation, max force and sets the default force.
    iRotation = 45;
    fMaxForce = 50;
    ChangeForce(15);

    // Instantiate the AI
    ai = new AI(fMaxForce, this);
}

Catapult::~Catapult()
{
    delete ai;
}

void Catapult::InitForceGauge()
{
    // UHH OH MAGIC NUMBERS
    forcegauge.iWindowSize = 1600;
    // Sets the size of the forcegauge.
    forcegauge.SetSize(3);
    // Sets the forcegauge's position to slightly above the catapult.
    forcegauge.Position = Position + Vector2D(-20, -50);
}

// Changes the current force and prevents it from becoming greater than the maximum force or lower than 0.
void Catapult::ChangeForce(int f)
{
    if(f < fMaxForce && f > 0)
        fForce = f;
    else if(f >= fMaxForce)
        fForce = fMaxForce;
    else if(f <= 0)
        fForce = 0;

    forcegauge.SetCurrentForce(fForce / fMaxForce);
}

// Rotates the catapult.
void Catapult::Rotate(int angle, bool CW)
{
    iRotation += CW ? angle : -angle;
}

void Catapult::Update()
{
    // Catapult calls the update for projectile, if it exists.
    if(proj)
		proj->Update();

    // If the projectile collides with something bCollisionActive is set to false. In that case, tell the AI the data gathered from the collision and destroy the projectile.
	if(proj && proj->bCollisionActive == false)
	{
        // Give the ai the data from the projectiles collision.
        ai->InsertData(proj->colData->colType);

		proj->Destroy();
		proj = NULL;

		SpawnProjectile();
	}
}

// Draws the projectile.
void Catapult::Draw()
{
    forcegauge.Draw();

    ai->graph->Draw();

    if(proj)
    	if(proj->bCollisionActive)
            proj->Draw();

    Vector2D vect1 = Vector2D(-iLength / 2, -iHeight / 2);
    Vector2D vect2 = Vector2D(iLength / 2, -iHeight / 2);
    Vector2D vect3 = Vector2D(iLength / 2, iHeight / 2);
    Vector2D vect4 = Vector2D(-iLength / 2, iHeight / 2);

    vect1 = vect1.Rotate(-iRotation) + Position + Vector2D(0, - iHeight / 2);
    vect2 = vect2.Rotate(-iRotation) + Position + Vector2D(0, - iHeight / 2);
    vect3 = vect3.Rotate(-iRotation) + Position + Vector2D(0, - iHeight / 2);
    vect4 = vect4.Rotate(-iRotation) + Position + Vector2D(0, - iHeight / 2);

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

void Catapult::SendDataToAI(CollisionData::CollisionType colType)
{
    ai->InsertData(colType);
}

// Spawns the projectile
void Catapult::SpawnProjectile()
{
	if(proj)										// If there already is a projectile active
	{
		proj->Destroy();							// then destroy it before creating a new one
		proj = NULL;
	}

    Vector2D vect = Vector2D(fForce, 0);
    vect = vect.Rotate(-iRotation);
    proj = new Projectile(Position, vect);
}
