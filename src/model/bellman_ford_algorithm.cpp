#include "bellman_ford_algorithm.h"

#include <iostream>
#include <format>
#include <limits>

#include "notifications.h"

namespace mvc
{
    bellman_ford_algorithm::bellman_ford_algorithm(int start_node, int target_node, std::vector<graph_node>& nodes)
        : graph_algorithm("Bellman-Ford", start_node), found_path(false), path(), target_node(target_node),
          distance(nodes.size(), std::numeric_limits<float>::max()), iteration(0), has_negative_cycle(false),
          current_node(start_node)
    {
        distance[start_node] = 0.0f;
        parent[start_node] = -1;
        nodes[start_node].set_visited(true);
    }

    bool bellman_ford_algorithm::step(mvc::graph& graph)
    {
        if (!found_path)
        {
            if (iteration < (int)graph.nodes.size() - 1)
            {
                // process only one node at a time in each step
                if (current_node < (int)graph.nodes.size()) 
                {
                    graph.highlight_node(current_node);
                    graph[current_node].set_visited(true);
                    
                    // process all the neighbors of the current node
                    for (int v : graph.nodes[current_node].get_neighbors())
                    {
                        float cost = graph.get_edge_cost(current_node, v);
                        if (distance[current_node] != std::numeric_limits<float>::max() && distance[current_node] + cost < distance[v])
                        {
                            distance[v] = distance[current_node] + cost;
                            parent[v] = current_node;
                        }
                    }
                    
                    current_node++;
                    return true; // wait
                }
                else
                {
                    iteration++;
                    web_ui::notifications::add("Bellman-Ford finished iteration " + std::to_string(iteration) + " of " + std::to_string((int)graph.nodes.size() - 1), 15);
                    current_node = start_node; // reset node to start the next iteration
                    return true; // wait
                }
            }
            else
            {
                // check for negative-weight cycles
                for (size_t u = 0; u < graph.nodes.size(); ++u)
                {
                    for (int v : graph.nodes[u].get_neighbors())
                    {
                        float cost = graph.get_edge_cost(u, v);
                        if (distance[u] != std::numeric_limits<float>::max() && distance[u] + cost < distance[v])
                        {
                            has_negative_cycle = true;
                            web_ui::notifications::add("Bellman-Ford detected a negative-weight cycle!", 15);
                            return false;  // not wait
                        }
                    }
                }

                // path construction after all iterations
                if (distance[target_node] == std::numeric_limits<float>::max())
                {
                    web_ui::notifications::add("Bellman-Ford could not find a path from node " + std::to_string(start_node) + " to node " + std::to_string(target_node), 15);
                    found_path = true;
                    return false;  // not wait
                }

                // construct the path
                int current = target_node;
                while (current != -1)
                {
                    path.push(current);
                    current = parent[current];
                }
                path.push(start_node);

                // reset graph state
                graph.unvisit_nodes();
                graph.highlight_node(-1);
                found_path = true;
                web_ui::notifications::add("Bellman-Ford found shortest path with " + std::to_string(path.size() - 2) + " steps and " + std::format("{:.2f}", distance[target_node]) + " total cost.", 15);
                
                return false;  // not wait
            }
        }
        else
        {
            // traversing through the path to visualize the shortest
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

    bool bellman_ford_algorithm::is_complete() const
    {
        return found_path && path.empty();
    }
}
