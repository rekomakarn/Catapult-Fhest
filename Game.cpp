#include "game.h"

using std::cout;

MyGame* MyGame::m_instance = NULL;

MyGame* MyGame::Instance(void)
{
    if(!m_instance)
    {
        m_instance = new MyGame();
    }
    return m_instance;
}

MyGame::MyGame(void)
{

}
MyGame::~MyGame(void)
{
    delete m_instance;
}

// These two might be useful for drawing lines I think?
void MyGame::SwapValues(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void MyGame::SwapCoordinates(Vector2D &obj)
{
    float temp = obj.x;
    obj.x = obj.y;
    obj.y = temp;
}

void MyGame::Run(int *argc, char** argv, int w, int h)
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    bRunning = true;
    screen = NULL;

    // OpenGL stuff
    // Decides how much memory OpenGL is allowed to use. I think.
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_WM_SetCaption("Catapult", NULL);

    screen = SDL_SetVideoMode(MAP_WIDTH, MAP_HEIGHT, 32, SDL_OPENGL);

    // I only divide in order to be able to use the RGB system. For whatever reason this function wants to use a double from 0 - 1
    glClearColor(0, 0.8, 1, 1);
    glViewport(0, 0, MAP_WIDTH, MAP_HEIGHT);

    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    Vector2D force = Vector2D(5, -10);

    // Map
    map = new Map(screen, 8);
    vect = map->GenerateBase(20, 30, false);
    map->GenerateBase(200, 10, true);

    // Catapult
    catapult.Position = vect;
    catapult.InitForceGauge();

    // Catapult AI (could be under catapult really but the projectile spawning is here at the moment)
    ai = new AI();

    // Test Particle
    part = new Particles();

    // This will run unless something tells it directly not to (user most likely)
    while(bRunning)
    {
        Update();       // This makes initilization and looping much easier to sepatata
        Draw();			// And we also make sure nothing draws to the screen before being updated
    }

    // Save all the map coordinates to a text file for later use
    map->SaveMap();

    // Do final cleanup
    delete(map);

    //Quit SDL
    SDL_Quit();

    return;
}

/*
 * This is the updates that are called by the main loop in Run();
 * After this Draw() is used to draw all the changes made by this function to the screen
 */
void MyGame::Update()
{
    bDebug = false;

    // Free Drawing
    bool bFreeDraw = false;

    start = SDL_GetTicks();

    Uint8* keystates = SDL_GetKeyState(NULL);

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                bRunning = false;
            break;

            case SDL_MOUSEMOTION:
                mx = event.motion.x;
                my = event.motion.y;
            break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_d)
                {
                    //map->CreateUndoPoint();
                }
                if(event.key.keysym.sym == SDLK_z)
                {
                    //map->RestoreUndoPoint();
                }
                if(event.key.keysym.sym == SDLK_b)
                {
                    map->GenerateBase(20, 30, false);
                    map->GenerateBase(180, 50, true);
                }
                if(event.key.keysym.sym == SDLK_p)
                {
                    catapult.SpawnProjectile();
                }
                if(event.key.keysym.sym == SDLK_PAGEUP)
                {
                    catapult.Rotate(false);
                }
                if(event.key.keysym.sym == SDLK_PAGEDOWN)
                {
                    catapult.Rotate(true);
                }
                if(event.key.keysym.sym == SDLK_KP_PLUS)
                {
                    catapult.ChangeForce(catapult.fForce + catapult.fMaxForce / 10);
                }
                if(event.key.keysym.sym == SDLK_KP_MINUS)
                {
                    catapult.ChangeForce(catapult.fForce - catapult.fMaxForce / 10);
                }
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_Quit();
                }
            break;
        }
    }

    if(keystates[SDLK_k])
    {
        bDebug = true;
    }
    else if(keystates[SDLK_d])
    {
        bFreeDraw = true;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glOrtho(0, MAP_WIDTH, MAP_HEIGHT, 0, -1, 1);

    glColor4ub(0, 255, 0, 255);

    catapult.Update();

    if(bFreeDraw)
    {
        map->FreeDraw(mx, my);
    }
    part->Update();

    // Call Draw() after everything is updated
    Draw();

    glPopMatrix();

    SDL_GL_SwapBuffers();

    if(1000 / FPS > SDL_GetTicks() - start)
        SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
}

/*
 * Draws the changes made by Update() to the screen
 */
void MyGame::Draw()
{
	// Draw the Catapult
    catapult.Draw();

    // Finally draw the whole map
    map->DrawMap(bDebug);
}
