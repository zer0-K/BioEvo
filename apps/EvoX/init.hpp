#pragma once

#include <GL/glew.h>    // must precede SDL_opengl.h

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "back/level_select.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <cstdio>
#include <string>
#include <utility>
#include <stdexcept>

namespace app_init
{

    void init_SDL()
    {
        // SDL2 init
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
            throw std::runtime_error(std::string("SDL_Init error: %s\n") + SDL_GetError());
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    }

    SDL_Window* create_window() 
    {
        SDL_Window* window = SDL_CreateWindow(
            "EvoX Engine",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            1280, 720,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

        if (!window) {
            throw std::runtime_error(std::string("SDL_CreateWindow error: ") + SDL_GetError());
        }

        return window;
    }

    SDL_GLContext create_context(SDL_Window* window)
    {
        SDL_GLContext gl_ctx = SDL_GL_CreateContext(window);
        return gl_ctx;
    }

    void init_ImGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    }

    void init_ImGui_style()
    {
        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding    = 6.0f;
        style.FrameRounding     = 4.0f;
        style.GrabRounding      = 4.0f;
        style.ItemSpacing       = {10, 8};
        style.WindowPadding     = {16, 16};
        style.Colors[ImGuiCol_WindowBg]         = ImVec4(0.10f, 0.12f, 0.14f, 1.0f);
        style.Colors[ImGuiCol_Button]           = ImVec4(0.18f, 0.45f, 0.28f, 1.0f);
        style.Colors[ImGuiCol_ButtonHovered]    = ImVec4(0.24f, 0.60f, 0.36f, 1.0f);
        style.Colors[ImGuiCol_ButtonActive]     = ImVec4(0.14f, 0.35f, 0.22f, 1.0f);
        style.Colors[ImGuiCol_SliderGrab]       = ImVec4(0.24f, 0.60f, 0.36f, 1.0f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.75f, 0.45f, 1.0f);
    }

    void init_backend()
    {
        back::level_select::build_menu_tree();
    }

    std::pair<SDL_Window*, SDL_GLContext> init()
    {
        init_SDL();

        SDL_Window* window = create_window(); 
        SDL_GLContext gl_ctx = create_context(window);
        SDL_GL_MakeCurrent(window, gl_ctx);

        glewExperimental = GL_TRUE;
        glewInit();  // must run after the GL context is current

        SDL_GL_SetSwapInterval(1); // vsync

        init_ImGui();
        init_ImGui_style();

        ImGui_ImplSDL2_InitForOpenGL(window, gl_ctx);
        ImGui_ImplOpenGL3_Init("#version 330");

        init_backend();

        return {window, gl_ctx};
    }
}
