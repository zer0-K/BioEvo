#pragma once

#include "../back/app_state.hpp"
#include "../back/tree.hpp"
#include "../back/level_select.hpp"
#include "common.hpp"

namespace front::choose_exp
{

    static void draw_main_window(ImGuiIO& io)
    {
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
        ImVec2 panel = {460, 480};
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

    static void draw_title()
    {
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
        front::common::CenterText("Experiments");
        ImGui::PopFont();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();
    }

    static void draw_experiment_buttons(back::app_state::AppState& state)
    {
        back::tree::Tree<std::string>::Node* n = back::level_select::menu.find(state.current_exp);
        auto children = back::level_select::menu.childrenOf(n);
        auto new_children = children;

        size_t i = 0;
        while (i < children.size())
        {
            if (front::common::CenterButton(children[i]->value.c_str()))
            {
                state.current_exp = children[i]->value;
                new_children = back::level_select::menu.childrenOf(children[i]);

                if(new_children.size() == 0)
                    state.start_simulation(children[i]);
                else
                {
                    children = new_children;
                    i = -1;
                }
            }
            
            ImGui::Spacing();
            i++;
        } 
    }

    static void draw_go_back_button(back::app_state::AppState& state)
    {
        back::tree::Tree<std::string>::Node* n = back::level_select::menu.find(state.current_exp);

        if (front::common::CenterButton("  Back  "))
        {
            n = back::level_select::menu.find(state.current_exp);
            if (n->isRoot())
                state.screen = back::app_state::AppScreen::MainMenu;
            else
                state.current_exp = n->parent->value;
        }
    }

    static void DrawExpMenu(back::app_state::AppState& state)
    {
        ImGuiIO& io = ImGui::GetIO();

        draw_main_window(io);
        draw_menu_panel(io);

        draw_title();

        ImGui::Spacing();

        draw_experiment_buttons(state);

        ImGui::Spacing();
        ImGui::Spacing();

        draw_go_back_button(state);

        ImGui::Spacing();

        if (front::common::CenterButton("  Quit  "))
            front::common::quit();

        ImGui::End();
    }

} // namespace front::main_menu
