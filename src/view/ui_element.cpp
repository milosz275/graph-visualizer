#include "ui_element.h"

#include "renderer.h"
#include "text.h"

namespace mvc
{
    ui_element::ui_element(glm::vec2 position, bool enabled) : position(position), enabled(enabled) {}
}
