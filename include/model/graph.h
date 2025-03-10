#pragma once

#include <vector>
#include <memory>
#include <tuple>

#include "graph_node.h"

namespace mvc
{
    class graph_state;

    class graph
    {
    protected:
        std::vector<graph_node> nodes;
        std::vector<std::tuple<int, int, float>> edges; // (node id, node id, cost)
        
    public:
        /**
         * @brief Creates default graph from Grokking Algorithms book.
         */
        graph();

        /**
         * @brief Creates graph in polygon shape of given vertices count.
         * @param vertices Polygon's vertex count.
         */
        graph(int vertices);

        /**
         * @brief Generates graph.
         * @param num_nodes Number of random nodes.
         * @param random False creates default graph.
         */
        graph(int num_nodes, bool random);

        /**
         * Clears the graph and creates default graph.
         */
        void create_default();

        /**
         * Clears the graph and generates polygon-based graph.
         */
        void generate_polygon(int vertices);

        /**
         * @brief Clears the graph and generates random graph.
         * @param num_nodes Number of nodes.
         * @param num_edges Number of edges.
         */
        void generate_random(int num_nodes, int num_edges);

        /**
         * @brief Sets all graph nodes as unvisited.
         */
        void unvisit_nodes();
        
        /**
         * @brief Draws entire graph including graph nodes, node identifiers, edges, edge costs.
         */
        void draw();

        /**
         * @brief Applies defined physics forces.
         */
        void apply_physics();

        /**
         * Explodes the graph by applying gigantic forces.
         */
        void explode();

        /**
         * @brief Returns the nodes count
         * @return Graph node count
         */
        int get_node_count();

        /**
         * @brief Supplies [] access to graph's nodes
         */
        graph_node& operator[](int id);

        /**
         * @brief Supplies [] access to graph's nodes
         */
        const graph_node& operator[](int id) const;

        friend class graph_state;
    };
}
