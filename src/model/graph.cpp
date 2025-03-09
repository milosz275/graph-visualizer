#include "graph.h"

#include <glm/glm.hpp>

#include "graph_physics.h"
#include "renderer.h"

namespace mvc
{
    void graph::create_default()
    {

    }

    void graph::generate_random(int num_nodes, int num_edges)
    {

    }

    void graph::run_algorithm_step()
    {

    }
    
    void graph::draw()
    {
        for (auto& edge : edges)
        {
            web_ui::renderer::draw_line(
                {nodes[edge.first].x, nodes[edge.first].y},
                {nodes[edge.second].x, nodes[edge.second].y},
                {0, 0, 0});
        }
        for (auto& node : nodes)
        {
            glm::vec3 color = {0, 0, 1};
            if (node.visited)
                color = {1, 0, 1};
            web_ui::renderer::draw_circle(
                {node.x, node.y},
                10.0,
                color);
        }
    }

    void graph::apply_physics()
    {
        graph_physics::apply_repulsion(nodes, 1000);
        graph_physics::apply_attraction(nodes, edges, 0.1, 50);
        graph_physics::apply_gravity(nodes, 0.05);
        graph_physics::update_nodes(nodes, 0.02, 0.9);
    }
}
