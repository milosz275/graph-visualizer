#include "graph.h"

#include <set>
#include <random>
#include <iostream>

#include <glm/glm.hpp>

#include "graph_node.h"
#include "graph_physics.h"
#include "renderer.h"

namespace mvc
{
    graph::graph()
    {
        create_default();
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

        // Create 5 default nodes
        for (int i = 0; i < 5; ++i)
        {
            graph_node node;
            node.id = i;
            node.x = -0.3f + i * 0.2f; // Spread them in X-axis
            node.y = 0.5f;
            nodes.push_back(node);
        }

        // Connect nodes sequentially
        edges.push_back({0, 1});
        edges.push_back({1, 2});
        edges.push_back({2, 3});
        edges.push_back({3, 4});
        
        // Update neighbor lists
        for (auto& edge : edges)
        {
            nodes[edge.first].neighbors.push_back(edge.second);
            nodes[edge.second].neighbors.push_back(edge.first);
        }
    }

    void graph::generate_random(int num_nodes, int num_edges)
    {
        nodes.clear();
        edges.clear();
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> pos_dist(-0.9f, 0.9f); // Random positions
        std::uniform_int_distribution<int> node_dist(0, num_nodes - 1); // Random node selection

        // Create nodes with random positions
        for (int i = 0; i < num_nodes; ++i)
        {
            graph_node node;
            node.id = i;
            node.x = pos_dist(gen);
            node.y = pos_dist(gen);
            nodes.push_back(node);
        }

        // Create random edges
        std::set<std::pair<int, int>> edge_set;
        while ((int)edge_set.size() < num_edges)
        {
            int a = node_dist(gen);
            int b = node_dist(gen);
            if (a != b && edge_set.find({a, b}) == edge_set.end() && edge_set.find({b, a}) == edge_set.end())
            {
                edge_set.insert({a, b});
                edges.push_back({a, b});
                nodes[a].neighbors.push_back(b);
                nodes[b].neighbors.push_back(a);
            }
        }
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
                {1.0f, 1.0f, 1.0f});
        }
        for (auto& node : nodes)
        {
            glm::vec3 color = {0.0f, 0.0f, 1.0f};
            if (node.visited)
                color = {1.0f, 0.0f, 1.0f};
            web_ui::renderer::draw_circle(
                {node.x, node.y},
                0.01f,
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
