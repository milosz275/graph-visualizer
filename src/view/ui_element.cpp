#include "ui_element.h"

#include "renderer.h"
#include "text.h"

namespace mvc
{
    ui_element::ui_element(glm::vec2 position, bool enabled) : position(position), enabled(enabled) {}

    bool ui_element::get_enabled() { return enabled; }

    bool ui_element::set_enabled(bool enabled) { return this->enabled = enabled; }

    bool ui_element::toggle_enabled() { return enabled = !enabled; }
}
