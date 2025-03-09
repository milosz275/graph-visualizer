#pragma once

#include <string>
#include <functional>

#include <glm/vec2.hpp>

#include "ui_element.h"

namespace mvc
{
    class ui_button : public ui_element
    {
    private:
        glm::vec2 size;
        std::string label;
        std::function<void()> callback;

    public:
        ui_button(glm::vec2 position, glm::vec2 min_size, std::string label, std::function<void()> callback, bool enabled = true);
        void render() override;
        bool is_clicked(glm::vec2 mouse) override;
        void on_click() override;
    };
}
