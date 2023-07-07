// A simple main entry for our game. Just sets up the game class, and runs it.
#include "game.hpp"

// Possibly move this onto heap in the future.
static auto game = Game();

#ifdef PLATFORM_WEB
/**
 *  Web requires a special way of handling infinite game loop
 *  It can be done automatically by compiling with Asyncify options, but setting emscripten_set_main_loop is a better and more performant way
 *  Also due to emscripten functions being C and requiring them to be free floating functions, we have to do it this special way
 */
#include <emscripten.h>
void mainWeb()
{
    game.GameLoop();
}

int main()
{
    game.Init();
    emscripten_set_main_loop(mainWeb, 0, 1);
    game.Quit();
    return 0;
}

#else

int main()
{
    game.Run();
    return 0;
}

#endif
