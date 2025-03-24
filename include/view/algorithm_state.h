#pragma once

#include <memory>

#include <glm/vec2.hpp>

#include "ui_state.h"
#include "graph.h"
#include "graph_algorithm.h"

namespace mvc
{
    class algorithm_state : public ui_state
    {
    private:
        std::unique_ptr<mvc::graph> graph;
        std::unique_ptr<mvc::graph_algorithm> algorithm;
        
    public:
        /**
         * @brief Sets up algorithm state and cancel button.
         * @param algorithm Algorithm runner object pointer
         * @param graph Graph object pointer
         */
        algorithm_state(std::unique_ptr<mvc::graph_algorithm> algorithm, std::unique_ptr<mvc::graph> graph);
        
        /**
         * @brief Destructor.
         */
        ~algorithm_state() override;

        /**
         * @brief Renders algorithm state including graph itself and runs specified algorithm.
         */
        void render() override;

        /**
         * @brief Updates current algorithm label as inactive menu button.
         */
        void update_algorithm_label_button();
    };
}
