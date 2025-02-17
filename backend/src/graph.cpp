#include "graph.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

static int counter = 0;

class graph_node
{
    int id;

public:
    graph_node() { id = counter++; }
    int get_id() const { return id; }
    bool operator==(const graph_node &other) const { return id == other.id; }

    friend ostream &operator<<(ostream &os, const graph_node &node)
    {
        os << "Node(" << node.id << ")";
        return os;
    }
};

struct graph_node_hash
{
    size_t operator()(const graph_node &node) const { return hash<int>()(node.get_id()); }
};

namespace std
{
    template <>
    struct hash<graph_node>
    {
        size_t operator()(const graph_node &node) const
        {
            return hash<int>()(node.get_id());
        }
    };
}

class directed_graph
{
    unordered_map<graph_node, unordered_map<graph_node, int>, graph_node_hash> edges;

public:
    unordered_map<graph_node, int> &operator[](const graph_node &node) { return edges[node]; }
    const unordered_map<graph_node, int> &operator[](const graph_node &node) const { return edges.at(node); }

    friend ostream &operator<<(ostream &os, const directed_graph &graph)
    {
        for (const auto &[node, neighbors] : graph.edges)
        {
            os << node << " -> { ";
            for (const auto &[neighbor, weight] : neighbors)
            {
                os << neighbor << " = " << weight << "; ";
            }
            os << "}\n";
        }
        return os;
    }

    void iterate_nodes_once(function<void(const graph_node &)> func) const
    {
        for (const auto &[node, _] : edges)
        {
            func(node);
        }
    }

    int get_node_count() const { return edges.size(); }

    auto begin() { return edges.begin(); }
    auto end() { return edges.end(); }

    auto begin() const { return edges.begin(); }
    auto end() const { return edges.end(); }
};

/*
directed_graph g;
graph_node a, b, c;

g[a][b] = 5;
g[a][c] = 3;
g[b][c] = 2;

// Print entire graph
cout << g << endl;

// Iterate through all nodes exactly once
cout << "Nodes in the graph: ";
g.iterate_nodes_once([](const graph_node &node)
                        { cout << node << " "; });
cout << endl;
*/