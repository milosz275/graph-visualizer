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
    protected:
        std::vector<graph_node> nodes;
        std::vector<std::tuple<int, int, float>> edges; // (node id, node id, cost)
        int highlighted_node;
        
    public:
        /**
         * @brief Creates base for directed/undirected graph.
         * @param num_nodes Node count reserved in the graph.
         */
        graph(int num_nodes);

        /**
         * @brief Destructor.
         */
        virtual ~graph() = default;

        /**
         * @brief Clears the graph and creates default graph.
         */
        virtual void create_default() = 0;

        /**
         * @brief Clears the graph and generates polygon-based graph.
         * @param vertices Vertices of the polygon - number of nodes.
         * @param random_weights Flag whether edges should random costs/weights.
         */
        virtual void generate_polygon(int vertices, bool random_weights) = 0;

        /**
         * @brief Clears the graph and generates random graph.
         * @param num_nodes Number of nodes.
         * @param random_weights Flag whether edges should random costs/weights.
         */
        virtual void generate_random(int num_nodes, bool random_weights) = 0;

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
        virtual void draw() = 0;

        /**
         * @brief Applies defined physics forces.
         */
        void apply_physics();

        /**
         * @brief Explodes the graph by applying gigantic forces.
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
         * @brief Finds cost/weight of edge between nodes u and v.
         * @return Returns cost of the edge, throws runtime_error if it does not exist.
         */
        float get_edge_cost(int u, int v);

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
