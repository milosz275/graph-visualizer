#include <bits/stdc++.h>

using namespace std;

static int counter = 0;

class graph_node
{
    int id;

public:
    graph_node() { id = counter++; };
    int get_id() { return id; };
    bool operator==(const graph_node &other) const { return id == other.id; }
};

struct graph_node_hash
{
    size_t operator()(const graph_node &node) const { return hash<int>()(((graph_node)node).get_id()); };
};

/**
 * Directed graph represented by connected nodes having references to its' neighbours.
 */
class directed_graph
{
    unordered_map<graph_node, unordered_map<graph_node, int>, graph_node_hash> edges;

public:
    unordered_map<graph_node, int> &operator[](const graph_node &node) { return edges[node]; }
    const unordered_map<graph_node, int> &operator[](const graph_node &node) const { return edges.at(node); }
};
