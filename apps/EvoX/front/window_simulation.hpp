#pragma once

#include <sstream>
#include <cctype>

#include "../back/app_state.hpp"
#include "../back/grid_fbo.hpp"
#include "simulation/simulation_constants.hpp"
#include "simulation/simulation_tab.hpp"
#include "simulation/advanced_editor_tab.hpp"

namespace front::simulation
{
    // ── Toolbar ───────────────────────────────────────────────────────────────────

    static void draw_toolbar(back::app_state::AppState& state, ImGuiIO& io)
    {
        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize({io.DisplaySize.x, TOOLBAR_H});
        ImGui::SetNextWindowBgAlpha(0.88f);
        ImGui::Begin("##toolbar", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize     |
            ImGuiWindowFlags_NoScrollbar);

        ImGui::SetCursorPosY(10);

        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
        front::common::CenterText(state.level.config.experiment_name.c_str());
        ImGui::PopFont();
        ImGui::Spacing();
        ImGui::Separator();

        if (ImGui::Button(state.level.running ? "  Pause  " : "  Play  "))
            state.level.running = !state.level.running;
        ImGui::SameLine();

        if (ImGui::Button("  Step  "))
        {
            state.level.running = false;
            if (state.level.editor_dirty) state.level.apply_editor();
            state.level.universe.step();
            if (!state.level.editor_dirty) state.level.load_editor();
        }
        ImGui::SameLine();

        if (ImGui::Button("  Reset  "))
        {
            state.level.running = false;
            state.level.universe.reset();
            state.level.load_editor();
        }
        ImGui::SameLine();

        if (ImGui::Button("  Save  "))
            state.level.universe.save_snapshot(std::string(state.level.save_dir));
        ImGui::SameLine();

        if (ImGui::Button(state.level.show_editor ? "Hide Editor" : "Show Editor"))
            state.level.show_editor = !state.level.show_editor;
        ImGui::SameLine();

        ImGui::Text("Step: %d", state.level.universe.step_count);

        if (!state.level.universe.last_error.empty())
        {
            ImGui::SameLine();
            ImGui::TextColored({1.0f, 0.35f, 0.35f, 1.0f},
                "| %s", state.level.universe.last_error.c_str());
        }

        ImGui::SameLine(io.DisplaySize.x - 150);
        if (ImGui::Button("  Main Menu  "))
        {
            state.exit_simulation();
            state.screen = back::app_state::AppScreen::MainMenu;
        }

        ImGui::End();
    }

    // ── Tab bar (thin window between toolbar and content) ─────────────────────────
    // Returns 0 = "Simulation", 1 = "Genetic editor"

    static int draw_tabbar(ImGuiIO& io)
    {
        static int active_tab = 0;

        ImGui::SetNextWindowPos({0, TOOLBAR_H});
        ImGui::SetNextWindowSize({io.DisplaySize.x, TABBAR_H});
        ImGui::SetNextWindowBgAlpha(0.90f);
        ImGui::Begin("##tabbar", nullptr,
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove       |
            ImGuiWindowFlags_NoResize     |
            ImGuiWindowFlags_NoScrollbar);

        if (ImGui::BeginTabBar("##main_tabs"))
        {
            if (ImGui::BeginTabItem("Simulation"))    { active_tab = 0; ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Genetic editor")) { active_tab = 1; ImGui::EndTabItem(); }
            ImGui::EndTabBar();
        }

        ImGui::End();
        return active_tab;
    }

    // ── Entry point ───────────────────────────────────────────────────────────────

    static void draw_simulation(back::app_state::AppState& state,
                                back::grid_fbo::GridFBO&   fbo)
    {
        ImGuiIO& io = ImGui::GetIO();
        draw_toolbar(state, io);
        int tab = draw_tabbar(io);
        if (tab == 0)
        {
            draw_cell_grid(state, fbo, io);
            if (state.level.show_editor)
                draw_basic_editor(state, io);
        }
        else
        {
            draw_genetic_editor(state, io);
        }
    }

} // namespace front::simulation
