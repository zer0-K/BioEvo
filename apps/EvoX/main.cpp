#include "init.hpp"
#include "cleanup.hpp"
#include "front/main_loop.hpp"

#include <SDL2/SDL_opengl.h>

int main(int /*argc*/, char* /*argv*/[])
{
    std::pair<SDL_Window*, SDL_GLContext> p = app_init::init();
    main_loop::run_main_loop(p);
    app_cleanup::cleanup(p);

    return 0;
}
