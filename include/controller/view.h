#pragma once

#include <glm/vec2.hpp>

namespace mvc
{
    class view
    {
    public:
        /**
         * @brief Gets canvas size. Wrapper to use freely during the loop.
         * @note It operates on a value updated once a cycle by web_ui.
         * @return Current canvas size
         */
        static glm::vec2 get_canvas_size();

        /**
         * @brief Translates given screen coordinates to graph app's coordinates system (-1.0f, 1.0f).
         * @param window_coordinates Coordinates in screen relative domain starting from upper left corner.
         * @return Coordinates translated into app's coordinate system.
         */
        static glm::vec2 get_coordinates(glm::vec2 window_coordinates);
    };
}
