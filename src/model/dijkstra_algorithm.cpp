#include "dijkstra_algorithm.h"

#include <iostream>
#include <format>
#include <limits>

#include "notifications.h"

namespace mvc
{
    dijkstra_algorithm::dijkstra_algorithm(int start_node, int target_node, std::vector<graph_node>& nodes)
        : graph_algorithm("Dijkstra", start_node), found_path(false), path(), target_node(target_node), distance(nodes.size(), std::numeric_limits<float>::max())
    {
        processed.insert({ 0, start_node }); // origin with cost equal 0
        distance[start_node] = 0.0f;
        parent[start_node] = -1;

        nodes[start_node].set_visited(true);
    }

    bool dijkstra_algorithm::step(mvc::graph& graph)
    {
        if (!found_path) // finding the shortest path
        {
            if (!processed.empty())
            {
                // get the node with smallest distance
                auto [current_cost, u] = *processed.begin();
                processed.erase(processed.begin());

                graph.highlight_node(u);

                // explore neighbors of node u
                for (int v : graph.nodes[u].get_neighbors())
                {
                    float cost = graph.get_edge_cost(u, v);

                    // relaxation step
                    if (distance[v] > distance[u] + cost)
                    {
                        if (distance[v] != std::numeric_limits<float>::max())
                            processed.erase(processed.find({ distance[v], v }));

                        distance[v] = distance[u] + cost;
                        parent[v] = u; // track previous node
                        processed.insert({ distance[v], v });

                        graph[v].set_visited(true);
                    }
                }
                return true; // not wait
            }
            else
            {
                int i = 0;
                std::cout << "Cost table:\n";
                for (float cost : distance)
                    std::cout << i++ << ": " << cost << '\n';

                if (distance[target_node] == std::numeric_limits<float>::max())
                {
                    web_ui::notifications::add("Dijkstra could not find shortest path from node " + std::to_string(start_node) + " to node " + std::to_string(target_node), 15);
                    found_path = true;
                    return false; // not wait
                }

                // construct target path
                int current = target_node;
                while (current != -1)
                {
                    path.push(current);
                    current = parent[current]; // move to the previous node in the path
                }
                path.push(start_node);

                // reset graph state
                graph.unvisit_nodes();
                graph.highlight_node(-1);
                found_path = true;
                web_ui::notifications::add("Dijkstra found shortest path with " + std::to_string((int)path.size() - 2) + " steps and " + std::format("{:.2f}", distance[target_node]) + " total cost.", 15);

                return false; // not wait
            }
            return true; // wait
        }
        else // traversing through the path to visualize the shortest
        {
            if (path.empty())
                return true; // wait

            int node_id = path.front();
            path.pop();

            graph[node_id].set_visited(true);
            graph.highlight_node(node_id);

            return true; // wait
        }
        return false; // not wait
    }

    bool dijkstra_algorithm::is_complete() const
    {
        return found_path && path.empty();
    }
}
