#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

/**
 * @brief Represents a node in the graph.
 */
class graph_node
{
    int id;     ///< Unique identifier for the node.
    float x, y; ///< Position of the node in the -1.0f - 1.0f domain.

public:
    /**
     * @brief Constructs a graph node with a unique identifier.
     */
    graph_node();

    /**
     * @brief Gets the unique identifier of the node.
     * @return The unique identifier of the node.
     */
    int get_id() const;

    /**
     * @brief Gets the x position of the node.
     * @return The x position of the node.
     */
    float get_x() const;

    /**
     * @brief Gets the y position of the node.
     * @return The y position of the node.
     */
    float get_y() const;

    /**
     * @brief Sets the x position of the node.
     * @param x The x position of the node.
     */
    void set_x(float x);

    /**
     * @brief Sets the y position of the node.
     * @param y The y position of the node.
     */
    void set_y(float y);

    /**
     * @brief Equality operator for comparing two graph nodes.
     * @param other The other graph node to compare with.
     * @return True if the nodes are equal, false otherwise.
     */
    bool operator==(const graph_node &other) const;

    /**
     * @brief Stream insertion operator for printing the graph node.
     * @param os The output stream.
     * @param node The graph node to print.
     * @return The output stream.
     */
    friend ostream &operator<<(ostream &os, const graph_node &node);
};

/**
 * @brief Hash function for graph_node to be used in unordered_map.
 */
struct graph_node_hash
{
    /**
     * @brief Computes the hash value for a graph node.
     * @param node The graph node to hash.
     * @return The hash value of the graph node.
     */
    size_t operator()(const graph_node &node) const;
};

namespace std
{
    template <>
    struct hash<graph_node>
    {
        /**
         * @brief Computes the hash value for a graph node.
         * @param node The graph node to hash.
         * @return The hash value of the graph node.
         */
        size_t operator()(const graph_node &node) const;
    };
}

/**
 * @brief Represents a directed graph with nodes and weighted edges.
 */
class directed_graph
{
    unordered_map<graph_node, unordered_map<graph_node, int>, graph_node_hash> edges; ///< Adjacency list representation of the graph.

public:
    /**
     * @brief Accesses the neighbors of a node.
     * @param node The node whose neighbors are to be accessed.
     * @return A reference to the map of neighbors and their edge weights.
     */
    unordered_map<graph_node, int> &operator[](const graph_node &node);

    /**
     * @brief Accesses the neighbors of a node (const version).
     * @param node The node whose neighbors are to be accessed.
     * @return A const reference to the map of neighbors and their edge weights.
     */
    const unordered_map<graph_node, int> &operator[](const graph_node &node) const;

    /**
     * @brief Stream insertion operator for printing the directed graph.
     * @param os The output stream.
     * @param graph The directed graph to print.
     * @return The output stream.
     */
    friend ostream &operator<<(ostream &os, const directed_graph &graph);

    /**
     * @brief Iterates through all nodes in the graph exactly once.
     * @param func The function to apply to each node.
     */
    void iterate_nodes(function<void(graph_node &)> func);

    /**
     * @brief Iterates through all edges in the graph exactly once.
     * @param func The function to apply to each edge.
     */
    void iterate_edges(function<void(const graph_node &, const graph_node &)> func) const;

    /**
     * @brief Gets the number of nodes in the graph.
     * @return The number of nodes in the graph.
     */
    int get_node_count() const;

    /**
     * @brief Gets an iterator to the beginning of the graph.
     * @return An iterator to the beginning of the graph.
     */
    auto begin();

    /**
     * @brief Gets an iterator to the end of the graph.
     * @return An iterator to the end of the graph.
     */
    auto end();

    /**
     * @brief Gets a const iterator to the beginning of the graph.
     * @return A const iterator to the beginning of the graph.
     */
    auto begin() const;

    /**
     * @brief Gets a const iterator to the end of the graph.
     * @return A const iterator to the end of the graph.
     */
    auto end() const;
};

#endif // GRAPH_H
