#pragma once

#include <string>
#include <functional>

#include <glm/vec2.hpp>

#include "ui_element.h"

namespace mvc
{
    class ui_label : public ui_element
    {
    private:
        std::string text;

    public:
        ui_label(glm::vec2 position, std::string text);
        void render() override;
        bool is_clicked(glm::vec2) override;
        void on_click() override;
    };
}
