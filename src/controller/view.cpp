#include "view.h"

#include "canvas.h"

namespace mvc
{
    glm::vec2 view::get_canvas_size()
    {
        return web_ui::canvas::get_canvas_size();
    }

    glm::vec2 view::get_coordinates(glm::vec2 window_coordinates)
    {
        glm::vec2 canvas = get_canvas_size();
        return { (2.0f * window_coordinates.x / canvas.x) - 1.0f, 1.0f - (2.0f * window_coordinates.y / canvas.y) };
    }
}
