#include "canvas.h"

#include <emscripten.h>
#include <emscripten/html5.h>

namespace web_ui
{
    glm::vec2 canvas::size;

    void canvas::update_canvas_size()
    {
        size = {EM_ASM_INT({ return getCanvasSize().width; }, 0), EM_ASM_INT({ return getCanvasSize().height; }, 0)};
    }

    glm::vec2 canvas::get_canvas_size()
    {
        return size;
    }
}
