#pragma once

#include <string>

#include <glm/vec2.hpp>

namespace mvc
{
    class ui_state
    {
    protected:
        std::string label;

    public:
        ui_state(std::string label);
        virtual ~ui_state() = default;
        
        /**
         * Renders menu and the graph
         */
        virtual void render() = 0;

        virtual void handle_click(glm::vec2 mouse, bool down) = 0;
        std::string get_label();
    };
}
