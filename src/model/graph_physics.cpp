#include "graph_physics.h"

namespace mvc
{
    void graph_physics::apply_repulsion(std::vector<graph_node>& nodes, float k_r)
    {
        for (size_t i = 0; i < nodes.size(); ++i)
        {
            for (size_t j = i + 1; j < nodes.size(); ++j)
            {
                float dx = nodes[i].x - nodes[j].x;
                float dy = nodes[i].y - nodes[j].y;
                float dist = sqrt(dx * dx + dy * dy + 1e-6);
                float force = k_r / (dist * dist);
    
                float fx = force * dx / dist;
                float fy = force * dy / dist;
    
                nodes[i].fx += fx;
                nodes[i].fy += fy;
                nodes[j].fx -= fx;
                nodes[j].fy -= fy;
            }
        }
    }

    void graph_physics::apply_attraction(std::vector<graph_node>& nodes, std::vector<std::pair<int, int>>& edges, float k_a, float rest_length)
    {
        for (auto& edge : edges)
        {
            int i = edge.first, j = edge.second;

            float dx = nodes[j].x - nodes[i].x;
            float dy = nodes[j].y - nodes[i].y;
            float dist = sqrt(dx * dx + dy * dy + 1e-6); // avoid zero division
            float force = k_a * (dist - rest_length);

            float fx = force * dx / dist;
            float fy = force * dy / dist;

            nodes[i].fx += fx;
            nodes[i].fy += fy;
            nodes[j].fx -= fx;
            nodes[j].fy -= fy;
        }
    }

    void graph_physics::apply_gravity(std::vector<graph_node>& nodes, float k_g)
    {
        for (auto& node : nodes)
        {
            float dx = -node.x;
            float dy = -node.y;
            node.fx += k_g * dx;
            node.fy += k_g * dy;
        }
    }

    void graph_physics::update_nodes(std::vector<graph_node>& nodes, float time_step, float damping)
    {
        for (auto& node : nodes)
        {
            node.vx = (node.vx + time_step * node.fx) * damping;
            node.vy = (node.vy + time_step * node.fy) * damping;
    
            node.x += time_step * node.vx;
            node.y += time_step * node.vy;
    
            // reset forces
            node.fx = node.fy = 0;
        }
    }
}
