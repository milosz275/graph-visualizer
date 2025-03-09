#pragma once

#include <string>
#include <memory>
#include <vector>

#include <glm/vec2.hpp>

#include "ui_state.h"
#include "ui_element.h"

namespace mvc
{
    class menu_state : public ui_state
    {
    private:
        std::vector<std::unique_ptr<mvc::ui_element>> elements;
        
    public:
        menu_state();
        ~menu_state() override;
        void render() override;
        void handle_click(glm::vec2 mouse, bool down) override;
    };
}
