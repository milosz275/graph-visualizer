#include "ui_label.h"

#include "text.h"

namespace mvc
{
    ui_label::ui_label(glm::vec2 position, std::string text) : ui_element(position), text(text) {}

    void ui_label::render()
    {
        // [ ] Add font size and color
        web_ui::text::draw_text({position.x, position.y}, text, "16px Arial", "gray");
    }

    bool ui_label::is_clicked(glm::vec2) { return false; } // label is non-clickable

    void ui_label::on_click() {}
}
