#include "graph_physics.h"

namespace mvc
{
    bool graph_physics::is_paused = false;

    bool graph_physics::paused() { return graph_physics::is_paused; }

    bool graph_physics::toggle_simulation() { return graph_physics::is_paused = !graph_physics::is_paused; }

    void graph_physics::apply_repulsion(std::vector<graph_node>& nodes, float k_r)
    {
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            for (size_t j = i + 1; j < nodes.size(); ++j)
            {
                float dx = nodes[i].position.x - nodes[j].position.x;
                float dy = nodes[i].position.y - nodes[j].position.y;
                float dist = sqrt(dx * dx + dy * dy + 1e-6);
                float force = k_r / (dist * dist);
    
                float fx = force * dx / dist;
                float fy = force * dy / dist;
    
                nodes[i].force_accumulator.x += fx;
                nodes[i].force_accumulator.y += fy;
                nodes[j].force_accumulator.x -= fx;
                nodes[j].force_accumulator.y -= fy;
            }
        }
    }

    void graph_physics::apply_attraction(std::vector<graph_node>& nodes, std::vector<std::tuple<int, int, float>>& edges, float k_a, float rest_length)
    {
        for (auto& edge : edges)
        {
            auto [i, j, cost] = edge;

            float dx = nodes[j].position.x - nodes[i].position.x;
            float dy = nodes[j].position.y - nodes[i].position.y;
            float dist = sqrt(dx * dx + dy * dy + 1e-6); // avoid zero division
            float force = k_a * (dist - rest_length) / cost;

            float fx = force * dx / dist;
            float fy = force * dy / dist;

            nodes[i].force_accumulator.x += fx;
            nodes[i].force_accumulator.y += fy;
            nodes[j].force_accumulator.x -= fx;
            nodes[j].force_accumulator.y -= fy;
        }
    }

    void graph_physics::apply_gravity(std::vector<graph_node>& nodes, float k_g)
    {
        for (auto& node : nodes)
        {
            float dx = -node.position.x;
            float dy = -node.position.y;
            node.force_accumulator.x += k_g * dx;
            node.force_accumulator.y += k_g * dy;
        }
    }

    void graph_physics::update_nodes(std::vector<graph_node>& nodes, float time_step, float damping)
    {
        for (auto& node : nodes)
        {
            node.velocity.x = (node.velocity.x + time_step * node.force_accumulator.x) * damping;
            node.velocity.y = (node.velocity.y + time_step * node.force_accumulator.y) * damping;
    
            node.position.x += time_step * node.velocity.x;
            node.position.y += time_step * node.velocity.y;
    
            // reset forces
            node.force_accumulator.x = node.force_accumulator.y = 0;
        }
    }

    void graph_physics::explode(std::vector<graph_node>& nodes, float explosion_force)
    {
        for (auto& node : nodes)
        {
            float dx = node.position.x;
            float dy = node.position.y;
            float dist = sqrt(dx * dx + dy * dy + 1e-6); // avoid zero division

            float fx = explosion_force * dx / dist;
            float fy = explosion_force * dy / dist;

            node.force_accumulator.x += fx;
            node.force_accumulator.y += fy;
        }
    }
}
