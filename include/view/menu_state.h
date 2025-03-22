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
        static bool undirected;

    public:
        /**
         * @brief Sets up graph generation menu.
         */
        menu_state();

        /**
         * @brief Descructor.
         */
        ~menu_state() override;

        /**
         * @brief Renders the scene including all menu elements.
         */
        void render() override;

        /**
         * 
         */
        bool toggle_undirected();
    };
}
