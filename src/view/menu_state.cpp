#include "menu_state.h"

#include <iostream>
#include <memory>

#include "text.h"
#include "app.h"
#include "renderer.h"
#include "ui_button.h"
#include "graph_state.h"
#include "canvas.h"
#include "background.h"
#include "undirected_graph.h"
#include "directed_graph.h"
#include "notifications.h"

namespace mvc
{
    bool menu_state::undirected = true;
    bool menu_state::random_weights = true;

    menu_state::menu_state() : ui_state("menu")
    {
        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, -0.9625f + 0.115f),
            glm::vec2(0.3f, 0.1f),
            "Undirected graph",
            [this]() {
                toggle_undirected();
            },
            !undirected));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f + 0.315f, -0.9625f + 0.115f),
            glm::vec2(0.3f, 0.1f),
            "Directed graph",
            [this]() {
                toggle_undirected();
            },
            undirected));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, -0.9625f),
            glm::vec2(0.3f, 0.1f),
            "Random weights",
            [this]() {
                toggle_random_weights();
            },
            !random_weights));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f + 0.315f, -0.9625f),
            glm::vec2(0.3f, 0.1f),
            "Uniform weights",
            [this]() {
                toggle_random_weights();
            },
            random_weights));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.35f, 0.10f),
            glm::vec2(0.325f, 0.10f),
            "Default",
            [this]() {
                std::unique_ptr<mvc::graph> new_graph = create_graph(7);
                new_graph->create_default();
                web_ui::notifications::add("Default graph selected.", 3);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.35f, -0.05f),
            glm::vec2(0.325f, 0.10f),
            "Pentagon",
            [this]() {
                std::unique_ptr<mvc::graph> new_graph = create_graph(5);
                new_graph->generate_polygon(5, random_weights);
                web_ui::notifications::add("Pentagon selected.", 3);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.35f, -0.20f),
            glm::vec2(0.325f, 0.10f),
            "Hexagon",
            [this]() {
                std::unique_ptr<mvc::graph> new_graph = create_graph(6);
                new_graph->generate_polygon(6, random_weights);
                web_ui::notifications::add("Hexagon selected.", 3);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.35f, -0.35f),
            glm::vec2(0.325f, 0.10f),
            "Hexadecagon (16)",
            [this]() {
                std::unique_ptr<mvc::graph> new_graph = create_graph(16);
                new_graph->generate_polygon(16, random_weights);
                web_ui::notifications::add("Hexadecagon selected.", 3);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.35f, -0.50f),
            glm::vec2(0.325f, 0.10f),
            "Triacontadigon (32)",
            [this]() {
                std::unique_ptr<mvc::graph> new_graph = create_graph(32);
                new_graph->generate_polygon(32, random_weights);
                web_ui::notifications::add("Triacontadigon selected.", 3);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(0.025f, 0.10f),
            glm::vec2(0.325f, 0.10f),
            "Random (8)",
            [this]() {
                std::unique_ptr<mvc::graph> new_graph = create_graph(8);
                new_graph->generate_random(8, random_weights);
                web_ui::notifications::add("Random graph with 8 nodes selected.", 3);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(0.025f, -0.05f),
            glm::vec2(0.325f, 0.10f),
            "Topological (8)",
            [this]() {
                std::unique_ptr<mvc::graph> new_graph = create_graph(8);
                new_graph->generate_topological(8, random_weights);
                web_ui::notifications::add("Topological graph with 8 nodes selected.", 3);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(0.025f, -0.20f),
            glm::vec2(0.325f, 0.10f),
            "Topological (16)",
            [this]() {
                std::unique_ptr<mvc::graph> new_graph = create_graph(16);
                new_graph->generate_topological(16, random_weights);
                web_ui::notifications::add("Topological graph with 16 nodes selected.", 3);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(0.025f, -0.35f),
            glm::vec2(0.325f, 0.10f),
            "Topological (32)",
            [this]() {
                std::unique_ptr<mvc::graph> new_graph = create_graph(32);
                new_graph->generate_topological(32, random_weights);
                web_ui::notifications::add("Topological graph with 32 nodes selected", 3);
                app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
            }));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(0.025f, -0.50f),
            glm::vec2(0.325f, 0.10f),
            "Load previous",
            []() {
                // [ ] Add loading graph from user input
            },
            false));

        elements.push_back(std::make_unique<ui_button>(
            glm::vec2(-0.975f, 0.75f),
            glm::vec2(0.3f, 0.1f),
            "Toggle background",
            []() {
                web_ui::background::toggle_darkmode();
            }));
    }

    menu_state::~menu_state() {}

    std::unique_ptr<mvc::graph> menu_state::create_graph(int num_nodes)
    {
        if (undirected)
            return std::make_unique<mvc::undirected_graph>(num_nodes);
        return std::make_unique<mvc::directed_graph>(num_nodes);
    }

    void menu_state::render()
    {
        glm::vec2 canvas = web_ui::canvas::get_canvas_size();
        web_ui::renderer::draw_rectangle({ -0.4f, -0.55f }, { 0.4f, 0.4f }, { 0.3f, 0.3f, 0.3f });
        web_ui::text::draw_text({ -1 * (417.5 / canvas.x), 0.275f }, "Choose graph generation", "36px Arial", "white");

        for (const auto& element : elements)
            element->render();
    }

    bool menu_state::toggle_undirected()
    {
        elements[0]->toggle_enabled();
        elements[1]->toggle_enabled();
        return undirected = !undirected;
    }

    bool menu_state::toggle_random_weights()
    {
        elements[2]->toggle_enabled();
        elements[3]->toggle_enabled();
        return random_weights = !random_weights;
    }
}
