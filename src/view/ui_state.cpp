#include "ui_state.h"

#include <iostream>

#include "mouse.h"

namespace mvc
{
    ui_state::ui_state(std::string label) : label(label) {}

    std::string ui_state::get_label() { return label; }

    void ui_state::handle_click(glm::vec2 mouse, bool down)
    {
        if (down)
            return;

        for (size_t i = 0; i < elements.size(); ++i)
            if (elements[i]->is_clicked({mouse.x, mouse.y}))
                elements[i]->on_click();
    }

    void ui_state::handle_hover(glm::vec2 mouse)
    {
        bool was_hovering = mvc::mouse::hover;
        mvc::mouse::hover = false;

        for (size_t i = 0; i < elements.size(); ++i)
        {
            if (elements[i]->is_enabled() && elements[i]->is_clicked({mouse.x, mouse.y}))
            {
                mvc::mouse::hover = true;
                break;
            }
        }

        if (mvc::mouse::hover != was_hovering)
        {
            if (mvc::mouse::hover)
                mvc::mouse::set_mouse_pointer();
            else
                mvc::mouse::set_mouse_cursor();
        }
    }
}
