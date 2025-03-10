#include "algorithm_state.h"

#include <glm/vec2.hpp>

#include "text.h"
#include "app.h"
#include "renderer.h"
#include "ui_button.h"
#include "graph.h"
#include "graph_state.h"
#include "app.h"

namespace mvc
{
    algorithm_state::algorithm_state(std::unique_ptr<mvc::graph_algorithm> algorithm, std::unique_ptr<mvc::graph> graph) : ui_state("algorithm"), graph(std::move(graph)), algorithm(std::move(algorithm))
    {
        elements.push_back(std::make_unique<ui_button>(glm::vec2(-0.975f, 0.75f), glm::vec2(0.3f, 0.1f), "Back to Graph", [this]() {
            this->graph->unvisit_nodes();
            app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(this->graph)));
        }));
    }

    algorithm_state::~algorithm_state() {}

    void algorithm_state::render()
    {
        graph->apply_physics();
        graph->draw();

        if (algorithm->check_timer())
        {
            if (algorithm->step(*this->graph) == false)
                algorithm->fast_forward_timer(); // do not sleep when step was empty
            if (algorithm->is_complete())
            {
                graph->unvisit_nodes();
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(graph)));
            }
        }

        for (const auto& element : elements)
            element->render();
    }
}
