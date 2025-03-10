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
        /**
         * @brief Creates UI label with given coordinates.
         * @param position Text coordinates.
         * @param text String text.
         */
        ui_label(glm::vec2 position, std::string text);

        /**
         * @brief Renders the label.
         */
        void render() override;

        /**
         * @brief Does nothing.
         * @note Label is not clickable.
         */
        bool is_clicked(glm::vec2) override;

        /**
         * @brief Does nothing.
         * @note Label is not clickable.
         */
        void on_click() override;
    };
}
