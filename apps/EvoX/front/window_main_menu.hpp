#pragma once

#include "../back/app_state.hpp"
#include "ui_helper.hpp"

namespace front::main_menu
{
    // ── General UI components ────────────────────────────────────

    static void draw_main_window(ImGuiIO& io)
    {
        // Full-screen transparent window as background canvas
        ImGui::SetNextWindowPos({0, 0});

        ImGui::SetNextWindowSize(io.DisplaySize);
        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGui::Begin("##bg", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoInputs     |
            ImGuiWindowFlags_NoNav        |
            ImGuiWindowFlags_NoBringToFrontOnFocus);
        ImGui::End();
    }

    static void draw_menu_panel(ImGuiIO& io)
    {
        // Centred menu panel
        ImVec2 panel = {420, 420};
        ImGui::SetNextWindowPos(
            {(io.DisplaySize.x - panel.x) * 0.5f,
            (io.DisplaySize.y - panel.y) * 0.5f});
        ImGui::SetNextWindowSize(panel);
        ImGui::SetNextWindowBgAlpha(0.92f);

        ImGui::Begin("##menu", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize);
        
        ImGui::Spacing();
        ImGui::Spacing();
    }

    // ── Menu panel UI components ─────────────────────────────────

    static void draw_title()
    {
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);   // use default (swap for big font in case)
        front::CenterText("EvoX Engine");
        ImGui::PopFont();

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();
    }

    static void draw_grid_settings(back::app_state::AppState& state)
    {
        ImGui::Text("Grid Settings");
        ImGui::Spacing();
        ImGui::SliderInt("Width",     &state.grid_width,  10, 200);
        ImGui::SliderInt("Height",    &state.grid_height, 10, 200);
        ImGui::SliderFloat("Cell px", &state.cell_size,   2.f, 20.f);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();
    }

    static void daw_about_popup(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowSize({320, 160}, ImGuiCond_Always);

        ImGui::SetNextWindowPos(
            {(io.DisplaySize.x - 320) * 0.5f,
            (io.DisplaySize.y - 160) * 0.5f},
            ImGuiCond_Always);

        if (ImGui::Begin("About##popup", &state.show_about,
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
        {
            ImGui::Spacing();
            CenterText("EvoX Engine v0.1");
            ImGui::Spacing();
            CenterText("Built with SDL2 + Dear ImGui + OpenGL");
            ImGui::Spacing();
            ImGui::Spacing();
            if (front::CenterButton("Close", {100, 30}))
                state.show_about = false;
        }
        ImGui::End();
    }

    static void quit()
    {
        SDL_Event quit;
        quit.type = SDL_QUIT;
        SDL_PushEvent(&quit);
    }

    // ── Draw all ─────────────────────────────────────────────────

    static void DrawMainMenu(back::app_state::AppState& state)
    {
        ImGuiIO& io = ImGui::GetIO();

        draw_main_window(io);
        draw_menu_panel(io);

        draw_title();

        draw_grid_settings(state);

        if (front::CenterButton("  Start Simulation  "))
            state.screen = back::app_state::AppScreen::Simulation;

        ImGui::Spacing();

        if (front::CenterButton("  About  "))
            state.show_about = true;

        ImGui::Spacing();

        if (front::CenterButton("  Quit  "))
            quit();

        ImGui::End(); // end of menu panel

        if (state.show_about)
            daw_about_popup(state, io);
    }
}
