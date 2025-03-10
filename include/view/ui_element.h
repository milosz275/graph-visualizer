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
        /**
         * @brief Allows overloading and creating UI element.
         * @param position UI element coordinates.
         * @param enabled Flag indicating if the element is active when created.
         */
        ui_element(glm::vec2 position, bool enabled = true);

        /**
         * @brief Descructor
         */
        virtual ~ui_element() = default;

        /**
         * @brief Allows overloading and rendering the UI element.
         */
        virtual void render() = 0;

        /**
         * @brief Allows overloading and checking for match in click event.
         */
        virtual bool is_clicked(glm::vec2) = 0;
        
        /**
         * @brief Allows overloading and connecting as on click event.
         */
        virtual void on_click() = 0;

        /**
         * @brief Returns whether UI element is currently enabled.
         * @return True if element is active, false otherwise.
         */
        bool is_enabled();
    };
}
