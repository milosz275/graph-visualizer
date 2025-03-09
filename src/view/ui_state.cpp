#include "ui_state.h"

namespace mvc
{
    ui_state::ui_state(std::string label) : label(label) {}
    std::string ui_state::get_label() { return label; }
}
