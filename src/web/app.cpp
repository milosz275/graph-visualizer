#include "app.h"

#include <iostream>

#include <glm/glm.hpp>

#include "renderer.h"
#include "text.h"
#include "mouse.h"
#include "background.h"
#include "menu_state.h"
#include "canvas.h"
#include "notifications.h"

namespace app
{
    bool graph_app::initialized;
    bool graph_app::running;
    std::unique_ptr<mvc::ui_state> graph_app::current_state;

    void graph_app::init()
    {
        if (initialized)
        {
            std::cout << "Graph App already initialized. Returning...\n";
            return;
        }
        current_state = std::make_unique<mvc::menu_state>();
        
        web_ui::text::setup_canvas();
        web_ui::renderer::init();
        mvc::mouse::connect_mouse_callbacks();

        initialized = true;
    }

    void graph_app::set_state(std::unique_ptr<mvc::ui_state> new_state)
    {
        current_state = std::move(new_state);
    }

    void graph_app::run()
    {
        if (running)
        {
            std::cout << "Graph App already running. Returning...\n";
            return;
        }
        if (!initialized)
            init();
        
        emscripten_set_main_loop(main_loop, 0, 1);
    }

    void graph_app::main_loop()
    {
        web_ui::canvas::update_canvas_size();
        web_ui::background::draw_background();
        web_ui::text::clear_text_canvas();
        draw_logo();
        draw_legend();
        web_ui::notifications::draw();
        current_state->render();
    }

    void graph_app::handle_mouse_click(glm::vec2 mouse, bool down)
    {
        current_state->handle_click(mouse, down);
    }

    void graph_app::handle_mouse_move(glm::vec2 mouse)
    {
        current_state->handle_hover(mouse);
    }

    void graph_app::draw_logo()
    {
        web_ui::text::draw_text_absolute({10.0f, 10.0f}, "Graph Visualizer", "32px Arial", "#2158b7");
    }

    void graph_app::draw_legend()
    {
        web_ui::renderer::draw_rectangle({0.85f - 0.02f, -0.875f + 0.05f}, {1.0f, -1.0f}, {0.4f, 0.4f, 0.4f});
        web_ui::text::draw_text({0.85f - 0.01f, -0.865f}, "Legend", "16px Arial", "white");

        web_ui::renderer::draw_circle(
            {0.85f, -0.90f},
            0.01f,
            {0.0f, 0.0f, 1.0f});
        web_ui::text::draw_text({0.862f, -0.9f - 0.01f}, "Unexplored", "16px Arial", "white");
        web_ui::renderer::draw_circle(
            {0.85f, -0.94f},
            0.01f,
            {0.0f, 0.8f, 0.8f});
        web_ui::text::draw_text({0.862f, -0.94f - 0.01f}, "Current", "16px Arial", "white");
        web_ui::renderer::draw_circle(
            {0.85f, -0.98f},
            0.01f,
            {1.0f, 0.0f, 1.0f});
        web_ui::text::draw_text({0.862f, -0.98f - 0.01f}, "Explored", "16px Arial", "white");
    }
}
