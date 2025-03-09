#include "ui_element.h"

#include "renderer.h"

namespace mvc
{
    bool ui_element::is_clicked(float mouse_x, float mouse_y)
    {
        return mouse_x >= x && mouse_x <= (x + width) && mouse_y >= y && mouse_y <= (y + height);
    }

    ui_button::ui_button(float x, float y, float width, float height, string label, function<void()> callback) : label(label), callback(callback)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
    void ui_button::render()
    {
        web_ui::renderer::draw_rectangle({x, y}, {x + width, y + height}, {0.9f, 0.9f, 0.9f});
    }
    void ui_button::on_click() { callback(); }

    ui_label::ui_label(float x, float y, string text) {}
    void ui_label::render() {}
    bool ui_label::is_clicked(float, float) { return false; } // non-clickable
    void ui_label::on_click() {}
}
