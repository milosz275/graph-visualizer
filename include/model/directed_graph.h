#pragma once

#include <vector>
#include <memory>
#include <tuple>

#include "graph.h"
#include "graph_node.h"

namespace mvc
{
    class graph_state;
    class dijkstra_algorithm;

    class directed_graph : public graph
    {
    public:
        /**
         * @brief Creates directed graph structure.
         * @param num_nodes Number of nodes reserved in the graph.
         */
        directed_graph(int num_nodes);

        /**
         * @brief Clears the graph and creates default directed graph.
         */
        void create_default() override;

        /**
         * @brief Clears the graph and generates polygon-based directed graph.
         * @param vertices Vertices of the polygon - number of nodes.
         * @param random_weights Flag whether edges should random costs/weights.
         */
        void generate_polygon(int vertices, bool random_weights) override;

        /**
         * @brief Clears the graph and generates random directed graph.
         * @param num_nodes Number of nodes.
         * @param random_weights Flag whether edges should random costs/weights.
         */
        void generate_random(int num_nodes, bool random_weights) override;

        /**
         * @brief Clears the graph and generates random topological directed graph.
         * @param num_nodes Number of nodes.
         * @param random_weights Flag whether edges should random costs/weights.
         */
        void generate_topological(int num_nodes, bool random_weights) override;

        /**
         * @brief Draws entire graph including graph nodes, node identifiers, edges, edge costs.
         */
        void draw() override;

        friend class graph_state;
        friend class dijkstra_algorithm;
    };
}
