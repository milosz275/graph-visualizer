#include "bfs_algorithm.h"

#include <format>

#include "notifications.h"

namespace mvc
{
    bfs_algorithm::bfs_algorithm(int start_node) : graph_algorithm("BFS", start_node)
    {
        queue.push({start_node, 0.0f});
    }

    bool bfs_algorithm::step(mvc::graph& graph)
    {
        if (queue.empty())
            return false; // not wait

        auto [node_id, cost] = queue.front();
        queue.pop();
        if (graph[node_id].get_visited())
            return false; // not wait
        if (node_id == graph.get_node_count() - 1) // assuming target is last
            web_ui::notifications::add("BFS: Destination achieved in " + std::to_string(current_step) + " steps with cost " + std::format("{:.2f}", cost) + ".", 15);

        graph[node_id].set_visited(true);
        graph.highlight_node(node_id);

        for (int neighbor : graph[node_id].get_neighbors())
        {
            if (!graph[neighbor].get_visited())
            {
                float total_cost = cost + graph.get_edge_cost(node_id, neighbor);
                queue.push({neighbor, total_cost});
                graph[neighbor].set_parent(node_id);
            }
        }
        current_step++;
        return true; // wait
    }

    bool bfs_algorithm::is_complete() const
    {
        return queue.empty();
    }
}
