#pragma once

#include <string>
#include <memory>
#include <vector>

#include <glm/vec2.hpp>

#include "ui_state.h"
#include "ui_element.h"

namespace mvc
{
    class graph;

    class menu_state : public ui_state
    {
    private:
        static bool undirected;
        static bool random_weights;

    public:
        /**
         * @brief Sets up graph generation menu.
         */
        menu_state();

        /**
         * @brief Destructor.
         */
        ~menu_state() override;

        /**
         * 
         */
        std::unique_ptr<mvc::graph> create_graph(int num_nodes);

        /**
         * @brief Renders the scene including all menu elements.
         */
        void render() override;

        /**
         * @brief Toggles whether graphs created by the menu state will be undirected or directed.
         * @return True for undirected, false otherwise.
         */
        bool toggle_undirected();

        /**
         * @brief Toggles whether graphs created by the menu state will have random weight edges.
         * @return True for random costs, false for uniform 1.0 costs.
         */
        bool toggle_random_weights();
    };
}
