#include "graph_state.h"

#include <iostream>

#include "text.h"
#include "renderer.h"
#include "ui_button.h"

namespace mvc
{
    graph_state::graph_state(std::unique_ptr<mvc::graph> graph) : ui_state("graph"), graph(std::move(graph))
    {
        elements.push_back(std::make_unique<ui_button>(glm::vec2(-0.9f, 0.9f), glm::vec2(0.3f, 0.1f), "Run Algorithm", []() {
            // Callback for "Run Algorithm"
        }));
    }

    graph_state::~graph_state()
    {
        
    }

    void graph_state::render()
    {
        web_ui::text::draw_text({0.0f, -0.95f}, "Graph");
        graph->draw();
    }

    void graph_state::handle_click(glm::vec2 mouse, bool down)
    {
        
    }
}
