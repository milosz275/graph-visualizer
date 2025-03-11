#include "ui_button.h"

#include "renderer.h"
#include "text.h"
#include "view.h"

namespace mvc
{
    ui_button::ui_button(glm::vec2 position, glm::vec2 min_size, std::string label, std::function<void()> callback, bool enabled) : ui_element(position, enabled), size(min_size), label(label), callback(callback) {}

    void ui_button::render()
    {
        glm::vec2 canvas = mvc::view::get_canvas_size();
        glm::vec3 background_color = {0.15f, 0.15f, 0.15f};
        std::string text_color = "white";
        if (!enabled)
        {
            background_color = {0.25f, 0.25f, 0.25f};
            text_color = "grey";
        }
        
        web_ui::renderer::draw_rectangle(
            {position.x, position.y},
            {position.x + size.x, position.y + size.y},
            background_color);

        web_ui::text::draw_text(
            {position.x + (25 / canvas.x), position.y + (size.y * 0.320)},
            label,
            "24px Arial",
            text_color);
    }

    bool ui_button::is_clicked(glm::vec2 mouse)
    {
        return mouse.x >= position.x && mouse.x <= (position.x + size.x) &&
            mouse.y >= position.y && mouse.y <= (position.y + size.y);
    }

    void ui_button::on_click() { if (enabled) callback(); }
}
