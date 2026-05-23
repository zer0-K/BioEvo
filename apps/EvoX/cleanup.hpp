#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <utility>

namespace app_cleanup
{
    void cleanup(std::pair<SDL_Window*, SDL_GLContext> p)
    {
        SDL_Window* window = p.first;
        SDL_GLContext gl_ctx = p.second;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        SDL_GL_DeleteContext(gl_ctx);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}