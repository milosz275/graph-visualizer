#pragma once

#include <glm/vec2.hpp>

namespace web_ui
{
    class canvas
    {
        static glm::vec2 size;

    public:
        /**
         * @brief UI's method to update current window size saved in static member with actual data from Emscripten by JS.
         */
        static void update_canvas_size();

        /**
         * @brief Returns JS obtained window size.
         * @return Canvas size
         */
        static glm::vec2 get_canvas_size();
    };
}
