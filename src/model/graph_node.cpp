#include "graph_node.h"

namespace mvc
{
    int graph_node::node_counter = 0;

    graph_node::graph_node() : id(node_counter++), position({ 0.0f, 0.0f }), velocity({ 0.0f, 0.0f }), force_accumulator({ 0.0f, 0.0f }), visited(false), highlighted(false), parent(-1) {}

    graph_node::graph_node(float x, float y) : id(node_counter++), position({ x, y }), velocity({ 0.0f, 0.0f }), force_accumulator({ 0.0f, 0.0f }), visited(false), highlighted(false), parent(-1) {}

    graph_node::graph_node(glm::vec2 position) : id(node_counter++), position(position), velocity({ 0.0f, 0.0f }), force_accumulator({ 0.0f, 0.0f }), visited(false), highlighted(false), parent(-1) {}

    glm::vec2 graph_node::get_position() { return position; }

    bool graph_node::get_visited() { return visited; }

    bool graph_node::set_visited(bool visited) { return this->visited = visited; }

    bool graph_node::set_highlighted(bool highlighted) { return this->highlighted = highlighted; }

    int graph_node::set_parent(int parent) { return this->parent = parent; }

    std::vector<int>& graph_node::get_neighbors() { return neighbors; }
}
