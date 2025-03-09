#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>

#include <glm/vec2.hpp>

namespace mvc
{
    class view
    {
    public:
        static glm::vec2 get_canvas_size();
        static glm::vec2 get_coordinates(glm::vec2 window_coordinates);
    };
}
