#include "algorithm_state.h"

#include <glm/vec2.hpp>

#include "text.h"
#include "app.h"
#include "renderer.h"
#include "ui_button.h"
#include "ui_label.h"
#include "graph.h"
#include "graph_state.h"
#include "app.h"
#include "graph_physics.h"

namespace mvc
{
    algorithm_state::algorithm_state(std::unique_ptr<mvc::graph_algorithm> algorithm, std::unique_ptr<mvc::graph> graph) : ui_state("algorithm"), graph(std::move(graph)), algorithm(std::move(algorithm))
    {
        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.75f),
            glm::vec2(0.3f, 0.1f),
            "Back to Graph",
            [this]() {
                this->graph->unvisit_nodes();
                this->graph->highlight_node(-1);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(this->graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, -0.9625f),
            glm::vec2(0.3f, 0.1f),
            "Toggle simulation",
            []() {
                graph_physics::toggle_simulation();
            }));

        // elements.push_back(std::make_unique<ui_button>(
        //     glm::vec2(-0.975f + 0.315f, -0.9625f), 
        //     glm::vec2(0.3f, 0.1f), 
        //     "Step forward",
        //     [&algorithm]() {
        //         algorithm->fast_forward_timer();
        //     }));
        
        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.60f),
            glm::vec2(0.3f, 0.1f),
            "",
            [](){},
            false)); // algorithm label placeholder
    }

    algorithm_state::~algorithm_state() {}

    void algorithm_state::render()
    {
        graph->apply_physics();
        graph->draw();
        draw_algorithm_button();

        if (algorithm->check_timer())
        {
            if (algorithm->step(*this->graph) == false)
                algorithm->fast_forward_timer(); // do not sleep when step was empty
            if (algorithm->is_complete())
            {
                graph->unvisit_nodes();
                graph->highlight_node(-1);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(graph)));
            }
        }

        for (const auto& element : elements)
            element->render();
    }

    void algorithm_state::draw_algorithm_button()
    {
        // assumes last element is algorithm placeholder/previous algorithm state to update
        elements.pop_back();
        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.60f),
            glm::vec2(0.3f, 0.1f),
            ("Algorithm: " + algorithm->get_label()).c_str(),
            [](){},
            false)); // algorithm label
    }
}
