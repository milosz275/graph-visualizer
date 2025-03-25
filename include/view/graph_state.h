#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>

#include "ui_state.h"
#include "ui_element.h"
#include "graph.h"

namespace mvc
{
    class graph_state : public ui_state
    {
    private:
        std::unique_ptr<mvc::graph> graph;

    public:
        /**
         * @brief Sets up graph algorithm menu and render the graph itself.
         * @param graph Graph object pointer
         */
        graph_state(std::unique_ptr<mvc::graph> graph);

        /**
         * @brief Destructor.
         */
        ~graph_state() override;

        /**
         * @brief Renders the scene including all menu elements and graph itself.
         */
        void render() override;
    };
}
