#include "graph.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

static int counter = 0;

graph_node::graph_node() { id = counter++; }

int graph_node::get_id() const { return id; }

float graph_node::get_x() const { return x; }

float graph_node::get_y() const { return y; }

void graph_node::set_x(float x) { this->x = x; }

void graph_node::set_y(float y) { this->y = y; }

bool graph_node::operator==(const graph_node &other) const { return id == other.id; }

ostream &operator<<(ostream &os, const graph_node &node)
{
    os << "Node(" << node.id << ")";
    return os;
}

size_t graph_node_hash::operator()(const graph_node &node) const { return hash<int>()(node.get_id()); }

size_t std::hash<graph_node>::operator()(const graph_node &node) const
{
    return hash<int>()(node.get_id());
}

unordered_map<graph_node, int> &directed_graph::operator[](const graph_node &node) { return edges[node]; }

const unordered_map<graph_node, int> &directed_graph::operator[](const graph_node &node) const { return edges.at(node); }

ostream &operator<<(ostream &os, const directed_graph &graph)
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

void directed_graph::iterate_nodes(function<void(graph_node &)> func)
{
    for (auto &pair : edges)
    {
        func(const_cast<graph_node&>(pair.first));
    }
}

void directed_graph::iterate_edges(function<void(const graph_node &, const graph_node &)> func) const
{
    for (const auto &[node, neighbors] : edges)
    {
        for (const auto &[neighbor, _] : neighbors)
        {
            func(node, neighbor);
        }
    }
}

int directed_graph::get_node_count() const { return edges.size(); }

auto directed_graph::begin() { return edges.begin(); }
auto directed_graph::end() { return edges.end(); }

auto directed_graph::begin() const { return edges.begin(); }
auto directed_graph::end() const { return edges.end(); }
