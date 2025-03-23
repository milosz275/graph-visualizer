#pragma once

#include <vector>
#include <memory>
#include <tuple>

#include "graph_node.h"

namespace mvc
{
    class graph_state;
    class dijkstra_algorithm;

    class graph
    {
    private:
        std::vector<graph_node> nodes;
        std::vector<std::tuple<int, int, float>> edges; // (node id, node id, cost)
        int highlighted_node;
        
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
         * @brief Clears the graph and creates default graph.
         */
        void create_default();

        /**
         * @brief Clears the graph and generates polygon-based graph.
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
         * @brief Unhighlights previous node and highlights node with given id.
         * @param node_id Node to be highlighted.
         */
        void highlight_node(int node_id);

        /**
         * @brief Draws given edge.
         * @param edge Edge to draw.
         */
        void draw_edge(std::tuple<int, int, float>& edge);
        
        /**
         * @brief Draws arrow pointing at the end of given edge.
         * @param edge Edge tip to draw.
         */
        void draw_arrow(std::tuple<int, int, float>& edge);
        
        /**
         * @brief Draws given node.
         * @param node Node to draw.
         */
        void draw_node(mvc::graph_node& node);

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
         * @brief Checks if there is at least one edge with negative cost/weight.
         * @return Returns true if there is at least one, false otherwise.
         */
        bool check_for_negative_edges();

        /**
         * @brief Supplies [] access to graph's nodes
         */
        graph_node& operator[](int id);

        /**
         * @brief Supplies [] access to graph's nodes
         */
        const graph_node& operator[](int id) const;

        friend class graph_state;
        friend class dijkstra_algorithm;
    };
}
