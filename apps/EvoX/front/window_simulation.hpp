#pragma once

#include "../back/app_state.hpp"


namespace front::simulation
{
    static void draw_main_window(ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({0, 0});
       
        ImGui::SetNextWindowSize({io.DisplaySize.x, 50});
        ImGui::SetNextWindowBgAlpha(0.88f);

        ImGui::Begin("##toolbar", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize     |
            ImGuiWindowFlags_NoScrollbar);

        ImGui::SetCursorPosY(10);
    }

    static void draw_simulation_viewport(back::app_state::AppState& state, ImGuiIO& io)
    {
        // ── Simulation viewport (placeholder) ─────────────────────────────────
        // In a real implementation you would:
        //   1. Render your grid to an OpenGL FBO (framebuffer object)
        //   2. Display it here with ImGui::Image()
        // For now we just draw a labelled empty area.

        float top = 50.0f;
        ImGui::SetNextWindowPos({0, top});
        ImGui::SetNextWindowSize({io.DisplaySize.x, io.DisplaySize.y - top});
        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGui::Begin("##viewport", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize     |
            ImGuiWindowFlags_NoInputs);

        // Draw a simple grid outline as a visual placeholder
        ImDrawList* draw = ImGui::GetWindowDrawList();
        float ox = 20.0f, oy = top + 20.0f;
        float cs = state.cell_size;
        int   W  = state.grid_width;
        int   H  = state.grid_height;

        ImU32 col_grid = IM_COL32(60, 120, 60, 200);
        ImU32 col_cell = IM_COL32(80, 200, 80, 80);

        // Draw a few "alive" cells as a static demo pattern (replace with real data)
        auto drawCell = [&](int x, int y) {
            ImVec2 p0 = {ox + x * cs, oy + y * cs};
            ImVec2 p1 = {p0.x + cs,   p0.y + cs};
            draw->AddRectFilled(p0, p1, col_cell);
        };
        // Glider pattern
        drawCell(1,0); drawCell(2,1); drawCell(0,2); drawCell(1,2); drawCell(2,2);

        // Grid lines
        for (int x = 0; x <= W; ++x)
            draw->AddLine({ox + x*cs, oy}, {ox + x*cs, oy + H*cs}, col_grid, 0.5f);
        for (int y = 0; y <= H; ++y)
            draw->AddLine({ox, oy + y*cs}, {ox + W*cs, oy + y*cs}, col_grid, 0.5f);

        // Status
        ImGui::SetCursorPos({10, io.DisplaySize.y - top - 30});
        ImGui::Text("Grid: %dx%d  |  Cell: %.0fpx  |  Status: %s",
            W, H, cs, state.running ? "Running" : "Paused");

        ImGui::End();
    }

    static void DrawSimulation(back::app_state::AppState& state)
    {
        ImGuiIO& io = ImGui::GetIO();

        draw_main_window(io);

        if (ImGui::Button(state.running ? "  Pause  " : "  Play  "))
            state.running = !state.running;

        ImGui::SameLine();
        if (ImGui::Button("  Step  "))
        {
            // TODO: advance simulation by one tick
        }

        ImGui::SameLine();
        if (ImGui::Button("  Reset  "))
        {
            // TODO: reset grid
        }

        ImGui::SameLine(io.DisplaySize.x - 140);
        if (ImGui::Button("  Main Menu  "))
            state.screen = back::app_state::AppScreen::MainMenu;

        ImGui::End();   // end of toolbar (defined in draw_main_window)

        draw_simulation_viewport(state, io);
    }
}
