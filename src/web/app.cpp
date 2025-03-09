#include "app.h"

#include "renderer.h"
#include "text.h"
#include "mouse.h"
#include "background.h"

using namespace std;

namespace app
{
    bool graph_app::initialized;
    bool graph_app::running;
    unique_ptr<mvc::ui_state> graph_app::current_state;

    void graph_app::init()
    {
        if (initialized)
        {
            std::cout << "Graph App already initialized. Returning...\n";
            return;
        }

        web_ui::text::setup_canvas();
        web_ui::renderer::init();
        mvc::mouse::connect_mouse_callbacks();

        current_state = make_unique<mvc::menu_state>();
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
        render_cycle();
        simulation_cycle();
    }

    void graph_app::render_cycle()
    {
        web_ui::background::draw_background();
        web_ui::text::clear_text_canvas();
        web_ui::text::draw_text_absolute();

        current_state->render();
    }

    void graph_app::simulation_cycle()
    {
        // graph state and algorithm state have the graph, that needs to be called with .apply_physics()
    }

    void graph_app::handle_mouse_click(int x, int y, bool down)
    {
        current_state->handle_click(x, y, down);
    }
}
