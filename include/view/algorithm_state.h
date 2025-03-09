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
        algorithm_state(std::unique_ptr<mvc::graph_algorithm> algorithm, std::unique_ptr<mvc::graph> graph);
        ~algorithm_state() override;
        void render() override;
        void handle_click(glm::vec2 mouse, bool down) override;
    };
}
