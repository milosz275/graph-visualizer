#pragma once

#include <emscripten.h>
#include <emscripten/html5.h>

#include <glm/vec2.hpp>

namespace mvc
{
    class mouse
    {
    public:

        static bool hover;

        static void connect_mouse_callbacks();

        static void set_mouse_cursor();

        static void set_mouse_pointer();

    private:

        static EM_BOOL mouse_click_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data);

        static EM_BOOL mouse_down_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data);

        static EM_BOOL mouse_up_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data);

        static EM_BOOL mouse_move_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data);
    };
}
