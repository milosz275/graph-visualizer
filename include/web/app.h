#pragma once

#include <iostream>
#include <memory>

#include <emscripten/html5.h>

#include "menu_state.h"
#include "graph_state.h"
#include "algorithm_state.h"

namespace mvc
{
    class mouse;
}

namespace app
{
    class graph_app
    {
    public:
        /**
         * Initializes the graph app.
         */
        static void init();

        /**
         * Runs the graph app.
         */
        static void run();
    
    private:
        static bool initialized;
        static bool running;
        static std::unique_ptr<mvc::ui_state> current_state;

        /**
         * Sets the new state of the app.
         * @param new_state New state to replace current.
         */
        static void set_state(std::unique_ptr<mvc::ui_state> new_state);

        /**
         * Main loop cycle.
         */
        static void main_loop();

        /**
         * Mouse click handler.
         * @param mouse Click coordinates.
         * @param down Flag whether click is up or down.
         */
        static void handle_mouse_click(glm::vec2 mouse, bool down);

        /**
         * Mouse move handler.
         * @param mouse Move coordinates.
         */
        static void handle_mouse_move(glm::vec2 mouse);

        /**
         * @brief Draws logo.
         */
        static void draw_logo();

        /**
         * @brief Draws legend.
         */
        static void draw_legend();

        friend class mvc::mouse;
        friend class mvc::menu_state;
        friend class mvc::graph_state;
        friend class mvc::algorithm_state;
    };
}
