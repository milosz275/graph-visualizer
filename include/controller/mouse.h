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

        /**
         * @brief Connects mouse callbacks.
         */
        static void connect_mouse_callbacks();

        /**
         * @brief Sets mouse cursor to default.
         */
        static void set_mouse_cursor();

        /**
         * @brief Sets mouse cursor to pointer.
         */
        static void set_mouse_pointer();

    private:
        /**
         * @brief Mouse click callback. Executed on both up/down clicks.
         */
        static EM_BOOL mouse_click_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data);

        /**
         * @brief Mouse down callback. Executed on mouse down event.
         */
        static EM_BOOL mouse_down_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data);

        /**
         * @brief Mouse up callback. Executed on mouse up event.
         */
        static EM_BOOL mouse_up_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data);

        /**
         * @brief Mouse move callback. Executed on any mouse movement.
         */
        static EM_BOOL mouse_move_callback(int event_type, const EmscriptenMouseEvent* e, void* user_data);
    };
}
