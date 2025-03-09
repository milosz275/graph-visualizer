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
        std::vector<std::unique_ptr<mvc::ui_element>> elements;
        
    public:
        graph_state(std::unique_ptr<mvc::graph> graph);
        ~graph_state() override;
        void render() override;
        void handle_click(glm::vec2 mouse, bool down) override;
    };
}
