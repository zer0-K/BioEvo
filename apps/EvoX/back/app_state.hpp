#pragma once

namespace back::app_state
{
    enum class AppScreen {
        MainMenu,
        Simulation,
    };

    struct AppState {
        AppScreen   screen      = AppScreen::MainMenu;
        bool        running     = true;
        bool        show_about  = false;
        int         grid_width  = 40;
        int         grid_height = 30;
        float       cell_size   = 16.0f;
    };
}
