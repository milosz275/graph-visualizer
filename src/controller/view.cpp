#include "view.h"

namespace mvc
{
    glm::vec2 view::get_canvas_size()
    {
        return {EM_ASM_INT({ return getCanvasSize().width; }, 0), EM_ASM_INT({ return getCanvasSize().height; }, 0)};
    }

    glm::vec2 view::get_coordinates(glm::vec2 window_coordinates)
    {
        glm::vec2 canvas = get_canvas_size();
        return {(2.0f * window_coordinates.x / canvas.x) - 1.0f, 1.0f - (2.0f * window_coordinates.y / canvas.y)};
    }
}
