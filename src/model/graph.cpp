#include "graph.h"

#include <set>
#include <random>
#include <deque>
#include <format>

#include <glm/glm.hpp>

#include "graph_node.h"
#include "graph_physics.h"
#include "renderer.h"
#include "text.h"
#include "background.h"

namespace mvc
{
    graph::graph(int num_nodes) : highlighted_node(-1)
    {
        nodes.reserve(num_nodes);
        edges.reserve(num_nodes * (num_nodes - 1) / 2);
    }

    void graph::unvisit_nodes()
    {
        for (auto& node : nodes)
            node.visited = false;
    }

    void graph::highlight_node(int node_id)
    {
        if (node_id > get_node_count() - 1 || node_id < -1)
            node_id = -1;
        if (highlighted_node != -1)
            nodes[highlighted_node].set_highlighted(false);
        highlighted_node = node_id;
        if (highlighted_node != -1)
            nodes[highlighted_node].set_highlighted(true);
    }

    void graph::draw_edge(std::tuple<int, int, float>& edge)
    {
        // edge
        auto [first_node, second_node, cost] = edge;
        web_ui::renderer::draw_line(
            {nodes[first_node].position.x, nodes[first_node].position.y},
            {nodes[second_node].position.x, nodes[second_node].position.y},
            {1.0f, 1.0f, 1.0f});

        // edge cost
        web_ui::text::draw_text(
            {(nodes[first_node].position.x + nodes[second_node].position.x) / 2 + 0.01f,
             (nodes[first_node].position.y + nodes[second_node].position.y) / 2 + 0.01f},
            std::format("{:.2f}", cost),
            "16px Arial",
            "gray");
    }

    void graph::draw_arrow(std::tuple<int, int, float>& edge)
    {
        auto [first_node, second_node, cost] = edge;
        float dx = nodes[second_node].position.x - nodes[first_node].position.x;
        float dy = nodes[second_node].position.y - nodes[first_node].position.y;
        float angle = atan2(dy, dx);

        float tip_length = 0.01f; // length of the triangle tip
        float tip_width = 0.005f;  // width of the triangle tip
        float node_radius = 0.01f; // radius of the node

        glm::vec2 tip_center = {
            nodes[second_node].position.x - node_radius * cos(angle),
            nodes[second_node].position.y - node_radius * sin(angle)};
        glm::vec2 tip_left = {
            tip_center.x - tip_length * cos(angle) - tip_width * sin(angle),
            tip_center.y - tip_length * sin(angle) + tip_width * cos(angle)};
        glm::vec2 tip_right = {
            tip_center.x - tip_length * cos(angle) + tip_width * sin(angle),
            tip_center.y - tip_length * sin(angle) - tip_width * cos(angle)};
        web_ui::renderer::draw_triangle(tip_center, tip_left, tip_right, {1.0f, 1.0f, 1.0f});
    }

    void graph::draw_node(mvc::graph_node& node)
    {
        // node
        glm::vec3 color = {0.0f, 0.0f, 1.0f};
        if (node.highlighted)
            color = {0.0f, 0.8f, 0.8f};
        else if (node.visited)
            color = {1.0f, 0.0f, 1.0f};
        web_ui::renderer::draw_circle(
            {node.position.x, node.position.y},
            0.01f,
            color);

        // node id
        if (node.id == 0)
            web_ui::text::draw_text(
                {node.position.x + 0.01f, node.position.y + 0.01f},
                "id: " + std::to_string(node.id),
                "16px Arial",
                "red");
        else if (web_ui::background::get_darkmode())
            web_ui::text::draw_text(
                {node.position.x + 0.01f, node.position.y + 0.01f},
                "id: " + std::to_string(node.id),
                "16px Arial",
                "white");
        else
            web_ui::text::draw_text(
                {node.position.x + 0.01f, node.position.y + 0.01f},
                "id: " + std::to_string(node.id),
                "16px Arial",
                "black");
    }

    void graph::apply_physics()
    {
        if (graph_physics::paused())
            return;
        graph_physics::apply_repulsion(nodes, 0.02f);
        graph_physics::apply_attraction(nodes, edges, 0.02f, 10.0f);
        graph_physics::apply_gravity(nodes, 2.5f);
        graph_physics::update_nodes(nodes, 0.02f, 0.9f);
    }

    void graph::explode()
    {
        graph_physics::explode(nodes, 10000.0f);
    }

    int graph::get_node_count()
    {
        return (int)nodes.size();
    }

    bool graph::check_for_negative_edges()
    {
        for (const auto& edge : edges)
        {
            auto [u, v, w] = edge;
            if (w < 0.0)
                return true;
        }
        return false;
    }

    float graph::get_edge_cost(int u, int v)
    {
        for (auto [e_u, e_v, e_w] : edges)
            if (e_u == u && e_v == v)
                return e_w;
        throw std::runtime_error("get_edge_cost: No edge from " + std::to_string(u) + " to " + std::to_string(u) + '.');
    }

    graph_node& graph::operator[](int id)
    {
        return nodes.at(id);
    }

    const graph_node& graph::operator[](int id) const
    {
        return nodes.at(id);
    }
}
