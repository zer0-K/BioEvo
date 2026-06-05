#pragma once

#include "../back/app_state.hpp"
#include "../back/grid_fbo.hpp"
#include "window_main_menu.hpp"
#include "window_choose_exp.hpp"
#include "window_simulation.hpp"

namespace main_loop
{

    inline bool process_event(back::app_state::AppState& state)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT)
                return true;

            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE &&
                state.screen == back::app_state::AppScreen::Simulation)
            {
                state.level.running = false;
                state.screen  = back::app_state::AppScreen::MainMenu;
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

        back::app_state::AppState state;
        back::grid_fbo::GridFBO   grid_fbo;
        grid_fbo.init();

        Uint32 last_tick = SDL_GetTicks();

        while (true)
        {
            if (process_event(state))
                break;

            // Delta time for auto-stepping
            Uint32 now = SDL_GetTicks();
            float  dt  = (now - last_tick) / 1000.0f;
            last_tick  = now;

            // Auto-step when running
            if (state.level.running &&
                state.screen == back::app_state::AppScreen::Simulation)
            {
                state.level.step_timer += dt;
                if (state.level.step_timer >= state.level.step_interval) {
                    state.level.step_timer = 0.0f;
                    state.level.universe.step();
                    // Refresh editor display if not dirty
                    if (state.level.selected_cell >= 0 && !state.level.editor_dirty)
                        state.level.load_editor();
                }
            }

            start_frame();

            switch (state.screen)
            {
                case back::app_state::AppScreen::MainMenu:
                    front::main_menu::DrawMainMenu(state);
                    break;
                case back::app_state::AppScreen::MenuExp:
                    front::choose_exp::DrawExpMenu(state);
                    break;
                case back::app_state::AppScreen::Simulation:
                    front::simulation::DrawSimulation(state, grid_fbo);
                    break;
            }

            render(window);
        }

        grid_fbo.destroy();
    }

} // namespace main_loop
