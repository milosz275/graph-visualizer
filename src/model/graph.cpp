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

namespace mvc
{
    graph::graph()
    {
        create_default();
    }

    graph::graph(int vertices)
    {
        generate_polygon(vertices);
    }

    graph::graph(int num_nodes, bool random)
    {
        if (random)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> edge_dist(0, num_nodes * (num_nodes - 1) / 2);
            int num_edges = edge_dist(gen);
            generate_random(num_nodes, num_edges);
        }
        else
            create_default();
    }

    void graph::create_default()
    {
        nodes.clear();
        edges.clear();

        graph_node node0;
        graph_node node1;
        graph_node node2;
        graph_node node3;
        graph_node node4;
        graph_node node5;
        graph_node node6;

        node0.id = 0;
        node1.id = 1;
        node2.id = 2;
        node3.id = 3;
        node4.id = 4;
        node5.id = 5;
        node6.id = 6;

        node0.x = -0.6f;
        node0.y = 0.0f;
        node1.x = -0.3f;
        node1.y = 0.5f;
        node2.x = -0.3f;
        node2.y = -0.5f;
        node3.x = 0.0f;
        node3.y = 0.0f;
        node4.x = 0.3f;
        node4.y = 0.5f;
        node5.x = 0.3f;
        node5.y = -0.5f;
        node6.x = 0.6f;
        node6.y = 0.0f;

        nodes.push_back(node0);
        nodes.push_back(node1);
        nodes.push_back(node2);
        nodes.push_back(node3);
        nodes.push_back(node4);
        nodes.push_back(node5);
        nodes.push_back(node6);

        edges.push_back({0, 1, 4.0f});
        edges.push_back({0, 2, 10.0f});
        edges.push_back({2, 3, 5.0f});
        edges.push_back({3, 4, 5.0f});
        edges.push_back({1, 4, 21.0f});
        edges.push_back({2, 5, 8.0f});
        edges.push_back({5, 4, 12.0f});
        edges.push_back({4, 6, 4.0f});

        for (auto& edge : edges)
        {
            auto [first_node, second_node, cost] = edge;
            nodes[first_node].neighbors.push_back(second_node);
            nodes[second_node].neighbors.push_back(first_node);
        }
    }

    void graph::generate_polygon(int vertices)
    {
        if (vertices < 3)
            return;
            
        nodes.clear();
        edges.clear();

        // build positions deque to construct polygon
        // 0 and n (n being the largest node i) are furthest (opposite sites of polygon)
        int num_nodes = vertices;
        float radius = 0.5f;
        std::deque<glm::vec2> positions;
        for (int i = 0; i < num_nodes; ++i)
        {
            float angle = 2.0f * M_PI * i / num_nodes; // angle in radians
            positions.push_back({radius * cos(angle), radius * sin(angle)});
        }

        // create n default nodes on a circle of radius 0.5
        int i = 0;
        while (!positions.empty())
        {
            glm::vec2 position = positions.front();
            positions.pop_front();

            graph_node node;
            node.id = i++;
            node.x = position.x;
            node.y = position.y;
            nodes.push_back(node);

            if (!positions.empty())
            {
                glm::vec2 position = positions.back();
                positions.pop_back();

                graph_node node;
                node.id = i++;
                node.x = position.x;
                node.y = position.y;
                nodes.push_back(node);
            }
        }

        // add edges following the pattern
        int max_even = (num_nodes % 2 == 0) ? num_nodes - 2 : num_nodes - 1;
        int max_odd = (num_nodes % 2 == 0) ? num_nodes - 1 : num_nodes - 2;

        // connect evens
        for (int i = 0; i < max_even; i += 2)
            edges.push_back({i, i + 2, 1.0f});

        // connect odds
        for (int i = 1; i < max_odd; i += 2)
            edges.push_back({i, i + 2, 1.0f});

        // connect the farthest nodes
        edges.push_back({max_even, max_odd, 1.0f});

        // connect last odd to first
        edges.push_back({1, 0, 1.0f});

        // update neighbor lists
        for (auto& edge : edges)
        {
            auto [first_node, second_node, cost] = edge;
            nodes[first_node].neighbors.push_back(second_node);
            nodes[second_node].neighbors.push_back(first_node);
        }
    }

    void graph::generate_random(int num_nodes, int num_edges)
    {
        nodes.clear();
        edges.clear();
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> pos_dist(-0.9f, 0.9f); // random positions
        std::uniform_int_distribution<int> node_dist(0, num_nodes - 1); // random node selection

        // create nodes with random positions
        for (int i = 0; i < num_nodes; ++i)
        {
            graph_node node;
            node.id = i;
            node.x = pos_dist(gen);
            node.y = pos_dist(gen);
            nodes.push_back(node);
        }

        // create random edges
        std::set<std::pair<int, int>> edge_set;
        while ((int)edge_set.size() < num_edges)
        {
            int a = node_dist(gen);
            int b = node_dist(gen);
            if (a != b && edge_set.find({a, b}) == edge_set.end() && edge_set.find({b, a}) == edge_set.end())
            {
                edge_set.insert({a, b});
                edges.push_back({a, b, 1.0f}); // default cost 1.0
                nodes[a].neighbors.push_back(b);
                nodes[b].neighbors.push_back(a);
            }
        }
    }

    void graph::unvisit_nodes()
    {
        for (auto& node : nodes)
        {
            node.highlighted = false;
            node.visited = false;
        }
    }
    
    void graph::draw()
    {
        for (auto& edge : edges)
        {
            // edge
            auto [first_node, second_node, cost] = edge;
            web_ui::renderer::draw_line(
                {nodes[first_node].x, nodes[first_node].y},
                {nodes[second_node].x, nodes[second_node].y},
                {1.0f, 1.0f, 1.0f});

            // edge cost
            web_ui::text::draw_text(
                {(nodes[first_node].x + nodes[second_node].x) / 2 + 0.01f,
                 (nodes[first_node].y + nodes[second_node].y) / 2 + 0.01f},
                std::format("{:.2f}", cost),
                "16px Arial",
                "gray");

            // // tip of the edge
            // float dx = nodes[second_node].x - nodes[first_node].x;
            // float dy = nodes[second_node].y - nodes[first_node].y;
            // float angle = atan2(dy, dx);

            // float tip_length = 0.01f; // length of the triangle tip
            // float tip_width = 0.005f;  // width of the triangle tip
            // float node_radius = 0.01f; // radius of the node

            // glm::vec2 tip_center = {
            //     nodes[second_node].x - node_radius * cos(angle),
            //     nodes[second_node].y - node_radius * sin(angle)};
            // glm::vec2 tip_left = {
            //     tip_center.x - tip_length * cos(angle) - tip_width * sin(angle),
            //     tip_center.y - tip_length * sin(angle) + tip_width * cos(angle)};
            // glm::vec2 tip_right = {
            //     tip_center.x - tip_length * cos(angle) + tip_width * sin(angle),
            //     tip_center.y - tip_length * sin(angle) - tip_width * cos(angle)};
            // web_ui::renderer::draw_triangle(tip_center, tip_left, tip_right, {1.0f, 1.0f, 1.0f});
        }
        for (auto& node : nodes)
        {
            // node
            glm::vec3 color = {0.0f, 0.0f, 1.0f};
            if (node.highlighted)
                color = {0.0f, 0.8f, 0.8f};
            else if (node.visited)
                color = {1.0f, 0.0f, 1.0f};
            web_ui::renderer::draw_circle(
                {node.x, node.y},
                0.01f,
                color);

            // node id
            if (node.id == 0)
                web_ui::text::draw_text(
                    {node.x + 0.01f, node.y + 0.01f},
                    "id: " + std::to_string(node.id),
                    "16px Arial",
                    "red");
            else
                web_ui::text::draw_text(
                    {node.x + 0.01f, node.y + 0.01f},
                    "id: " + std::to_string(node.id),
                    "16px Arial",
                    "black");
        }
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

    graph_node& graph::operator[](int id)
    {
        return nodes.at(id);
    }

    const graph_node& graph::operator[](int id) const
    {
        return nodes.at(id);
    }
}
