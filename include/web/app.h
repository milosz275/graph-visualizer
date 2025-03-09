#pragma once

#include <iostream>
#include <memory>

#include <emscripten/html5.h>

#include "menu_state.h"
#include "graph_state.h"

namespace mvc
{
    class mouse;
}

namespace app
{
    class graph_app
    {
    public:
        static void init();
        static void run();
    
    private:
        static bool initialized;
        static bool running;
        static std::unique_ptr<mvc::ui_state> current_state;

        static void set_state(std::unique_ptr<mvc::ui_state> new_state);
        static void main_loop();
        static void render_cycle();
        static void simulation_cycle();
        static void handle_mouse_click(glm::vec2 mouse, bool down);

        friend class mvc::mouse;
        friend class mvc::menu_state;
        friend class mvc::graph_state;
    };
}
