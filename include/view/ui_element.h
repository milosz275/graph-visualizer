#pragma once

#include <string>
#include <functional>

#include <glm/vec2.hpp>

namespace mvc
{
    class ui_element
    {
    protected:
        glm::vec2 position;
        bool enabled;

    public:
        ui_element(glm::vec2 position, bool enabled = true);
        virtual ~ui_element() = default;

        virtual void render() = 0;
        virtual bool is_clicked(glm::vec2) = 0;
        virtual void on_click() = 0;
    };
}
