#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glm/vec2.hpp>

#include "ui_element.h"

namespace mvc
{
    class ui_state
    {
    protected:
        std::string label;
        std::vector<std::unique_ptr<mvc::ui_element>> elements;

    public:
        /**
         * @brief Initializes ui_state base class with a label.
         */
        ui_state(std::string label);

        /**
         * @brief Descructor.
         */
        virtual ~ui_state() = default;
        
        /**
         * @brief Renders menu and the graph.
         */
        virtual void render() = 0;

        /**
         * @brief Returns state's label.
         * @return Label
         */
        std::string get_label();

        /**
         * @brief Handles mouse click.
         * @param mouse Click coordinates.
         * @param down Flag whether it is mouse_up or mouse_down.
         */
        void handle_click(glm::vec2 mouse, bool down);

        /**
         * @brief Handles mouse hover.
         * @param mouse Move coordinates.
         */
        void handle_hover(glm::vec2 mouse);
    };
}
