#include "algorithm_state.h"

#include <glm/vec2.hpp>

#include "text.h"
#include "app.h"
#include "renderer.h"
#include "ui_button.h"

namespace mvc
{
    algorithm_state::algorithm_state(std::unique_ptr<mvc::graph_algorithm> algorithm, std::unique_ptr<mvc::graph> graph) : ui_state("algorithm")
    {
        
    }

    algorithm_state::~algorithm_state()
    {
        
    }

    void algorithm_state::render()
    {
        
    }

    void algorithm_state::handle_click(glm::vec2 mouse, bool down)
    {
        
    }
}
