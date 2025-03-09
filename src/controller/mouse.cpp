#include "mouse.h"

#include <iostream>

#include "app.h"
#include "view.h"

namespace mvc
{
    void mouse::connect_mouse_callbacks()
    {
        emscripten_set_click_callback("#webglCanvas", nullptr, EM_TRUE, mouse_click_callback);
        emscripten_set_mousedown_callback("#webglCanvas", nullptr, EM_TRUE, mouse_down_callback);
        emscripten_set_mouseup_callback("#webglCanvas", nullptr, EM_TRUE, mouse_up_callback);
        emscripten_set_mousemove_callback("#webglCanvas", nullptr, EM_TRUE, mouse_move_callback);
    }

    EM_BOOL mouse::mouse_click_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data)
    {
        return EM_TRUE;
    }

    EM_BOOL mouse::mouse_down_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data)
    {
        app::graph_app::handle_mouse_click(view::get_coordinates({e->clientX, e->clientY}), true);
        return EM_TRUE;
    }

    EM_BOOL mouse::mouse_up_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data)
    {
        app::graph_app::handle_mouse_click(view::get_coordinates({e->clientX, e->clientY}), false);
        return EM_TRUE;
    }

    EM_BOOL mouse::mouse_move_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data)
    {
        return EM_TRUE;
    }
}
