#include "graph_state.h"

#include <iostream>

#include "text.h"
#include "renderer.h"
#include "ui_button.h"
#include "app.h"
#include "algorithm_state.h"
#include "bfs_algorithm.h"
#include "dfs_algorithm.h"
#include "dijkstra_algorithm.h"
#include "graph_physics.h"
#include "notifications.h"

namespace mvc
{
    graph_state::graph_state(std::unique_ptr<mvc::graph> graph) : ui_state("graph"), graph(std::move(graph))
    {
        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.75f),
            glm::vec2(0.3f, 0.1f),
            "Back to Menu",
            []() {
                app::graph_app::set_state(std::make_unique<mvc::menu_state>());
            }));
        
        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, -0.9625f), 
            glm::vec2(0.3f, 0.1f), 
            "Toggle physics", 
            []() {
                bool state = graph_physics::toggle_simulation();
                if (state)
                    web_ui::notifications::add("Simulation physics turned on.", 3);
                else
                    web_ui::notifications::add("Simulation physics turned off.", 3);
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.60f),
            glm::vec2(0.3f, 0.1f),
            "Run BFS", [this](){
                std::unique_ptr<mvc::graph_algorithm> algorithm = std::make_unique<mvc::bfs_algorithm>(0);
                app::graph_app::set_state(std::make_unique<mvc::algorithm_state>(std::move(algorithm), std::move(this->graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.45f),
            glm::vec2(0.3f, 0.1f),
            "Run DFS",
            [this]() {
                std::unique_ptr<mvc::graph_algorithm> algorithm = std::make_unique<mvc::dfs_algorithm>(0);
                app::graph_app::set_state(std::make_unique<mvc::algorithm_state>(std::move(algorithm), std::move(this->graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.30f),
            glm::vec2(0.3f, 0.1f),
            "Run Dijkstra",
            [this]() {
                std::unique_ptr<mvc::graph_algorithm> algorithm = std::make_unique<mvc::dijkstra_algorithm>(0, (int)this->graph->get_node_count() - 1, this->graph->nodes);
                app::graph_app::set_state(std::make_unique<mvc::algorithm_state>(std::move(algorithm), std::move(this->graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.15f),
            glm::vec2(0.3f, 0.1f),
            "Run A*", []() {
                std::cout << "Run A* callback\n";
            },
            false));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.00f),
            glm::vec2(0.3f, 0.1f),
            "Run Bellman-Ford",
            []() {
                std::cout << "Run Bellman-Ford callback\n";
            },
            false));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, -0.15f),
            glm::vec2(0.3f, 0.1f), 
            "Run all", []() {
                std::cout << "Run all callback\n";
            },
            false));
    }

    graph_state::~graph_state() {}

    void graph_state::render()
    {
        graph->apply_physics();
        graph->draw();

        for (const auto& element : elements)
            element->render();
    }
}
