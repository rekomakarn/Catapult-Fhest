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
    delete map;
    delete catapult;
    delete base;
    delete screen;
    delete m_instance;
}

void MyGame::Run(int *argc, char** argv, int w, int h)
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    // bRunning is saved in order to later check if the user wants to exit the program.
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

    // Sets thet window caption
    SDL_WM_SetCaption("Catapult", NULL);

    // Initializes the screen, and tells it to use opengl.
    screen = SDL_SetVideoMode(MAP_WIDTH, MAP_HEIGHT, 32, SDL_OPENGL);

    // I only divide in order to be able to use the RGB system. For whatever reason this function wants to use a double from 0 - 1
    glClearColor(0, 0.8, 1, 1);

    // Sets the viewport to be the entire map
    glViewport(0, 0, MAP_WIDTH, MAP_HEIGHT);

    // Sets the shade model
    glShadeModel(GL_SMOOTH);

    // Sets the projection mode. In this case only need 2D and thusly we use GL_PROJECTION
    glMatrixMode(GL_PROJECTION);
    // Saves the projection mode and settings
    glLoadIdentity();

    // Sets the default force
    Vector2D force = Vector2D(5, -10);
    Vector2D vect2;
    // Creates a new map and initializes it.
    map = new Map(screen, 8, Vector2D(MAP_WIDTH, MAP_HEIGHT));
    vect = map->GenerateBase(20, 30, false);
    vect2 = map->GenerateBase(200, 10, true);

    base = new Base(vect2.x, vect2.y);

    // Initializes the catapult and it's components.
    catapult = new Catapult();
    catapult->Position = vect;
    catapult->InitForceGauge();

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

    // Saves the ticks to set an FPS-cap
    start = SDL_GetTicks();

    // Saves the keystate of the keyboard. Used to allow input.
    Uint8* keystates = SDL_GetKeyState(NULL);

    SDL_Event event;
    // Input
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
                    catapult->ai->DecideNewForce();
                }
                if(event.key.keysym.sym == SDLK_PAGEUP)
                {
                    catapult->Rotate(5, false);
                }
                if(event.key.keysym.sym == SDLK_PAGEDOWN)
                {
                    catapult->Rotate(5, true);
                }
                if(event.key.keysym.sym == SDLK_KP_PLUS)
                {
                    catapult->ChangeForce(catapult->fForce + catapult->fMaxForce / 20);
                }
                if(event.key.keysym.sym == SDLK_KP_MINUS)
                {
                    catapult->ChangeForce(catapult->fForce - catapult->fMaxForce / 20);
                }
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    bRunning = false;
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

    catapult->Update();

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
    glBegin(GL_QUADS);
    glColor4ub(255, 50, 0, 255);
    glVertex2i(0, MAP_HEIGHT);
    glVertex2i(MAP_WIDTH, MAP_HEIGHT);
    glColor4ub(17, 150, 255, 255);
    glVertex2i(MAP_WIDTH, 0);
    glVertex2i(0, 0);
    glEnd();

    catapult->Draw();

    base->Draw();

    // Finally draw the whole map
    map->DrawMap(bDebug);
}
