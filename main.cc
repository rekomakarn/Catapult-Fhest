#include "game.h"

int main(int argc, char** argv)
{
    MyGame *game = MyGame::Instance();
    game->Run(&argc,argv, 640, 480);

    return EXIT_SUCCESS;
}
