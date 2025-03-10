#include "dijkstra_algorithm.h"

namespace mvc
{
    dijkstra_algorithm::dijkstra_algorithm(int start_node, int target_node, std::vector<graph_node>& nodes) : target_node(target_node)
    {
        pq.push({0, start_node});
        costs[start_node] = 0;

        for (const auto& node : nodes)
        {
            if (node.id != start_node)
                costs[node.id] = INFINITY;
        }
    }

    bool dijkstra_algorithm::step(mvc::graph& graph)
    {
        if (!found_path) // finding the shortest path
        {
            if (pq.empty())
                return false;

            auto [current_cost, node_id] = pq.top();
            pq.pop();

            if (processed.find(node_id) != processed.end())
                return false;

            processed.insert(node_id);
            graph[node_id].visited = true;

            // process neighbors
            for (int neighbor : graph[node_id].neighbors)
            {
                float new_cost = current_cost + 1; // assuming uniform edge weight
                if (new_cost < costs[neighbor])
                {
                    costs[neighbor] = new_cost;
                    parents[neighbor] = node_id;
                    pq.push({new_cost, neighbor});
                }
            }

            // if target found, reconstruct path
            if (node_id == target_node)
            {
                int step = target_node;
                while (step != -1)
                {
                    path.push(step);
                    if (parents.find(step) == parents.end())
                        break; // avoid accessing invalid key
                    step = parents[step];
                }
                path.push(0); // readd first element
                found_path = true;
            }
            return true;
        }
        else // traversing through the path
        {
            graph.unvisit_nodes();

            if (path.empty())
                return true;

            int node_id = path.front();
            path.pop();
            graph[node_id].visited = true;
            return true;
        }
        return false;
    }

    bool dijkstra_algorithm::is_complete() const
    {
        return found_path && path.empty();
    }
}
