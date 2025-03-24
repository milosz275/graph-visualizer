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
        /**
         * @brief Creates button at given position, with minimum size, label, callback and enable flag.
         * @param position Button coordinates.
         * @param min_size Minimum size of button to render. Might render larger when text label is longer.
         * @param label Text label.
         * @param callback Function executed on click event.
         * @param enabled Flag indicating current button status, false would gray out the button, defaults to true.
         */
        ui_button(glm::vec2 position, glm::vec2 min_size, std::string label, std::function<void()> callback, bool enabled = true);

        /**
         * @brief Renders the button along with its' label.
         */
        void render() override;

        /**
         * @brief Returns whether supplied coordinates fall into boxes dimensions.
         * @param mouse Click coordinates.
         * @return True when click is in the box.
         */
        bool is_clicked(glm::vec2 mouse) override;

        /**
         * Executes the callback on click event.
         */
        void on_click() override;

        /**
         * @brief Sets and returns new label.
         * @param label New label.
         */
        void set_label(std::string label);
    };
}
