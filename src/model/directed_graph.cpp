#include "directed_graph.h"

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
    directed_graph::directed_graph(int num_nodes) : graph(num_nodes) {}

    void directed_graph::create_default()
    {
        nodes.clear();
        edges.clear();
        graph_node::node_counter = 0;

        graph_node node0(-0.6f, 0.0f);
        graph_node node1(-0.3f, 0.5f);
        graph_node node2(-0.3f, -0.5f);
        graph_node node3(0.0f, 0.0f);
        graph_node node4(0.3f, 0.5f);
        graph_node node5(0.3f, -0.5f);
        graph_node node6(0.6f, 0.0f);

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
        }
    }

    void directed_graph::generate_polygon(int vertices, bool random_weights)
    {
        if (vertices < 3)
            return;
            
        nodes.clear();
        edges.clear();
        graph_node::node_counter = 0;

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
        while (!positions.empty())
        {
            glm::vec2 position = positions.front();
            positions.pop_front();

            graph_node node(position);
            nodes.push_back(node);

            if (!positions.empty())
            {
                glm::vec2 position = positions.back();
                positions.pop_back();

                graph_node node(position);
                nodes.push_back(node);
            }
        }

        // add edges following the pattern
        int max_even = (num_nodes % 2 == 0) ? num_nodes - 2 : num_nodes - 1;
        int max_odd = (num_nodes % 2 == 0) ? num_nodes - 1 : num_nodes - 2;

        // generate costs
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> cost_gen(random_weights ? 1.0f : 1.0f, random_weights ? 2.0f : 1.0f);
        float cost = cost_gen(gen);

        // connect evens
        for (int i = 0; i < max_even; i += 2)
        {
            edges.push_back({i, i + 2, cost});
            cost = cost_gen(gen);
        }

        // connect odds
        for (int i = 1; i < max_odd; i += 2)
        {
            edges.push_back({i, i + 2, cost});
            cost = cost_gen(gen);
        }

        // connect the farthest nodes
        edges.push_back({max_even, max_odd, cost});
        cost = cost_gen(gen);

        // connect last odd to first
        edges.push_back({1, 0, cost});
        cost = cost_gen(gen);

        // update neighbor lists
        for (auto& edge : edges)
        {
            auto [first_node, second_node, cost] = edge;
            nodes[first_node].neighbors.push_back(second_node);
        }
    }

    void directed_graph::generate_random(int num_nodes, bool random_weights)
    {
        nodes.clear();
        edges.clear();
        graph_node::node_counter = 0;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> pos_dist(-0.9f, 0.9f); // random positions
        std::uniform_int_distribution<int> node_dist(0, num_nodes - 1); // random node selection
        std::uniform_real_distribution<float> cost_gen(random_weights ? 1.0f : 1.0f, random_weights ? 2.0f : 1.0f);
        float cost = cost_gen(gen);
        
        int max_edges = num_nodes * (num_nodes - 1) / 2;
        std::uniform_int_distribution<int> num_edges_gen(max_edges / 3, max_edges / 2); // random edge count
        int num_edges = num_edges_gen(gen);

        // create nodes with random positions
        for (int i = 0; i < num_nodes; ++i)
        {
            graph_node node(pos_dist(gen), pos_dist(gen));
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
                edges.push_back({a, b, cost});
                nodes[a].neighbors.push_back(b);
                cost = cost_gen(gen);
            }
        }
    }

    void directed_graph::draw()
    {
        for (auto& edge : edges)
        {
            draw_edge(edge);
            draw_arrow(edge);
        }
        for (auto& node : nodes)
            draw_node(node);
    }
}
