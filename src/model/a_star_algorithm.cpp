#include "a_star_algorithm.h"

#include <iostream>
#include <format>
#include <limits>
#include <cmath>

#include "notifications.h"

namespace mvc
{
    a_star_algorithm::a_star_algorithm(int start_node, int target_node, std::vector<graph_node>& nodes)
        : graph_algorithm("A*", start_node), found_path(false), path(), target_node(target_node),
          g_cost(nodes.size(), std::numeric_limits<float>::max()),
          f_cost(nodes.size(), std::numeric_limits<float>::max())
    {
        open_set.insert({0, start_node});
        g_cost[start_node] = 0.0f;
        f_cost[start_node] = heuristic(nodes[start_node].get_position(), nodes[target_node].get_position());
        parent[start_node] = -1;

        nodes[start_node].set_visited(true);
    }

    float a_star_algorithm::heuristic(glm::vec2 node_pos, glm::vec2 goal_pos)
    {
        return std::sqrt(std::pow(node_pos.x - goal_pos.x, 2) + std::pow(node_pos.y - goal_pos.y, 2));
    }

    bool a_star_algorithm::step(mvc::graph& graph)
    {
        if (!found_path)
        {
            if (!open_set.empty())
            {
                auto [current_f, u] = *open_set.begin();
                open_set.erase(open_set.begin());

                graph.highlight_node(u);

                if (u == target_node)
                {
                    found_path = true;
                    int current = target_node;
                    while (current != -1)
                    {
                        path.push(current);
                        current = parent[current];
                    }
                    path.push(start_node);
                    graph.unvisit_nodes();
                    graph.highlight_node(-1);
                    web_ui::notifications::add("A* found path with " + std::to_string(path.size() - 2) + " steps and " + std::format("{:.2f}", g_cost[target_node]) + " total cost.", 15);
                    return false;
                }

                for (int v : graph.nodes[u].get_neighbors())
                {
                    float cost = graph.get_edge_cost(u, v);
                    float tentative_g = g_cost[u] + cost;

                    if (tentative_g < g_cost[v])
                    {
                        if (g_cost[v] != std::numeric_limits<float>::max())
                            open_set.erase(open_set.find({f_cost[v], v}));

                        g_cost[v] = tentative_g;
                        f_cost[v] = g_cost[v] + heuristic(graph.nodes[v].get_position(), graph.nodes[target_node].get_position());
                        parent[v] = u;
                        open_set.insert({f_cost[v], v});

                        graph[v].set_visited(true);
                    }
                }
                return true;
            }
            else
            {
                web_ui::notifications::add("A* could not find a path from node " + std::to_string(start_node) + " to node " + std::to_string(target_node), 15);
                found_path = true;
                return false;
            }
        }
        else
        {
            if (path.empty())
                return true;

            int node_id = path.front();
            path.pop();

            graph[node_id].set_visited(true);
            graph.highlight_node(node_id);

            return true;
        }
        return false;
    }

    bool a_star_algorithm::is_complete() const
    {
        return found_path && path.empty();
    }
}
