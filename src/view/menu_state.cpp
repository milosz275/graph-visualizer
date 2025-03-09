#include "menu_state.h"

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
        elements.push_back(std::make_unique<ui_button>(glm::vec2(-0.5f, 0.5f), glm::vec2(0.35f, 0.1f), "Generate Random Graph", []() {
            // callback for "Generate Random Graph"
        }));
        elements.push_back(std::make_unique<ui_button>(glm::vec2(-0.5f, 0.3f), glm::vec2(0.35f, 0.1f), "Load Graph", []() {
            // callback for "Load Graph"
        }, false));
    }

    menu_state::~menu_state()
    {
        
    }

    void menu_state::render()
    {
        web_ui::text::draw_text({-0.6f, 0.7f}, "Graph Visualizer Menu", "40px serif", "white");

        for (const auto& element : elements)
            element->render();
    }

    void menu_state::handle_click(glm::vec2 mouse, bool down)
    {
        if (down)
            return;

        for (size_t i = 0; i < elements.size(); ++i)
        {
            if (elements[i]->is_clicked({mouse.x, mouse.y}))
            {
                if (i == 0)
                {
                    // Generate new graph and switch state
                    std::unique_ptr<mvc::graph> new_graph = std::make_unique<mvc::graph>(10, true); // 10 random nodes
                    app::graph_app::set_state(std::make_unique<mvc::graph_state>(std::move(new_graph)));
                }
                else if (i == 1)
                {
                    // [ ] Add loading graph from user input
                }
            }
        }
    }
}
