#include "algorithm_state.h"

#include <iostream>
#include <format>

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
#include "notifications.h"

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
            "Toggle physics",
            []() {
                bool state = graph_physics::toggle_simulation();
                if (state)
                    web_ui::notifications::add("Simulation physics turned off.", 3);
                else
                    web_ui::notifications::add("Simulation physics turned on.", 3);
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f + 0.315f, -0.9625f), 
            glm::vec2(0.3f, 0.1f), 
            "Quicker step",
            [algorithm = this->algorithm.get()]() {
                if (algorithm)
                    web_ui::notifications::add("New simulation step length: " + std::format("{:.3f}", algorithm->speed_up()), 3);
            }));
        
        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f + 0.315f * 2, -0.9625f), 
            glm::vec2(0.3f, 0.1f), 
            "Slower step",
            [algorithm = this->algorithm.get()]() {
                if (algorithm)
                    web_ui::notifications::add("New simulation step length: " + std::format("{:.3f}", algorithm->slow_down()), 3);
            }));
        
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
        update_algorithm_label_button();

        try
        {
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
        }
        catch (std::runtime_error& error)
        {
            std::cerr << error.what() << '\n';
            graph->unvisit_nodes();
            graph->highlight_node(-1);
            app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(graph)));
        }

        for (const auto& element : elements)
            element->render();
    }

    void algorithm_state::update_algorithm_label_button()
    {
        // assumes last element is algorithm label button
        auto& last_element = elements.back();
        auto* button = dynamic_cast<ui_button*>(last_element.get());
        if (button)
            button->set_label("Algorithm: " + algorithm->get_label());
    }
}
