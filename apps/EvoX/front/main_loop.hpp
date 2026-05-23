#pragma once

#include "../back/app_state.hpp"
#include "window_main_menu.hpp"
#include "window_simulation.hpp"
#include "ui_helper.hpp"


namespace main_loop
{
    inline bool process_event(back::app_state::AppState state)
    {
        /** Return true if user wants to exit */
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT)
            {
                return true;
            }
            
            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE &&
                state.screen == back::app_state::AppScreen::Simulation)
            {
                state.screen = back::app_state::AppScreen::MainMenu;
            }
        }

        return false;
    }

    inline void start_frame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    inline void render(SDL_Window* window)
    {
        ImGui::Render();
        int w, h;
        SDL_GL_GetDrawableSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.08f, 0.10f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    void run_main_loop(std::pair<SDL_Window*, SDL_GLContext> p)
    {
        SDL_Window* window = p.first;
        //SDL_GLContext gl_ctx = p.second;

        back::app_state::AppState state;

        while (true)
        {
            bool do_exit = process_event(state);
            if (do_exit)
                goto exit;

            start_frame();

            // draw active screen (cannot be put in a function)
            switch (state.screen)
            {
                case back::app_state::AppScreen::MainMenu:
                    front::main_menu::DrawMainMenu(state);
                    break;
                case back::app_state::AppScreen::Simulation:
                    front::simulation::DrawSimulation(state);
                    break;
            }

            render(window);
        }
    exit:
        ;
    }
}
