#include "menu_state.h"

#include <iostream>
#include <memory>

#include "text.h"
#include "app.h"
#include "renderer.h"
#include "ui_button.h"
#include "graph_state.h"

namespace mvc
{
    menu_state::menu_state() : ui_state("menu")
    {
        elements.push_back(std::make_unique<ui_button>(glm::vec2(-0.35f, 0.10f), glm::vec2(0.3f, 0.1f), "Create default", []() {
            std::unique_ptr<mvc::graph> new_graph = std::make_unique<mvc::graph>();
            app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
        }));

        elements.push_back(std::make_unique<ui_button>(glm::vec2(-0.35f, -0.05f), glm::vec2(0.3f, 0.1f), "Generate pentagon", []() {
            std::unique_ptr<mvc::graph> new_graph = std::make_unique<mvc::graph>(5);
            app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
        }));

        elements.push_back(std::make_unique<ui_button>(glm::vec2(-0.35f, -0.20f), glm::vec2(0.3f, 0.1f), "Generate hexagon", []() {
            std::unique_ptr<mvc::graph> new_graph = std::make_unique<mvc::graph>(6);
            app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
        }));

        elements.push_back(std::make_unique<ui_button>(glm::vec2(-0.35f, -0.35f), glm::vec2(0.3f, 0.1f), "Generate random", []() {
            std::unique_ptr<mvc::graph> new_graph = std::make_unique<mvc::graph>(10, true);
            app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
        }));

        elements.push_back(std::make_unique<ui_button>(glm::vec2(-0.35f, -0.50f), glm::vec2(0.3f, 0.1f), "Load", []() {
            std::cout << "Load callback\n";
            // [ ] Add loading graph from user input
        }, false));
    }

    menu_state::~menu_state() {}

    void menu_state::render()
    {
        web_ui::renderer::draw_rectangle({-0.4f, -0.55f}, {0.4f, 0.4f}, {0.225f, 0.225f, 0.225f});
        web_ui::text::draw_text({-0.15f, 0.3f}, "Choose graph generation", "40px serif", "white");

        for (const auto& element : elements)
            element->render();
    }
}
