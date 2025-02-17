#include "graph.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

using namespace std;

static int counter = 0;

graph_node::graph_node()
{
    id = counter++;
    x = 0.0f;
    y = 0.0f;
}

int graph_node::get_id() const { return id; }

bool graph_node::get_selected() const { return selected; }

void graph_node::set_selected(bool selected) { this->selected = selected; }

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
    os << "Graph nodes:\n";
    for (const auto &[node, neighbors] : graph.edges)
    {
        os << node << " -> { ";
        for (const auto &[neighbor, weight] : neighbors)
        {
            os << neighbor << " = " << weight << "; ";
        }
        os << "}\n";
    }
    graph.iterate_nodes([&os](graph_node &node)
                        { os << node << "is selected: " << node.get_selected() << '\n'; });

    os << "Graph edges\n";
    graph.iterate_edges([&os](const graph_node &start, const graph_node &end)
                        { os << start << " -> " << end << '\n'; });
    return os;
}

void directed_graph::iterate_nodes(function<void(graph_node &)> func) const
{
    for (auto &pair : edges)
    {
        func(const_cast<graph_node &>(pair.first));
    }
}

void directed_graph::iterate_nodes_by_id(function<void(graph_node &)> func) const
{
    vector<graph_node> nodes;
    for (const auto &pair : edges)
    {
        nodes.push_back(pair.first);
    }

    sort(nodes.begin(), nodes.end(), [](const graph_node &a, const graph_node &b)
         { return a.get_id() < b.get_id(); });

    for (auto &node : nodes)
    {
        func(const_cast<graph_node &>(node));
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
int directed_graph::get_edge_count() const
{
    int count = 0;
    iterate_edges([&count](const graph_node &, const graph_node &)
                  { count++; });
    return count;
}

auto directed_graph::begin() { return edges.begin(); }
auto directed_graph::end() { return edges.end(); }

auto directed_graph::begin() const { return edges.begin(); }
auto directed_graph::end() const { return edges.end(); }
