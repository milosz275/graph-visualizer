#include "bfs_algorithm.h"

#include "notifications.h"

namespace mvc
{
    bfs_algorithm::bfs_algorithm(int start_node) : graph_algorithm("BFS")
    {
        queue.push(start_node);
    }

    bool bfs_algorithm::step(mvc::graph& graph)
    {
        if (queue.empty())
            return false; // not wait

        int node_id = queue.front();
        queue.pop();
        if (node_id == graph.get_node_count() - 1) // assuming target is last
            web_ui::notifications::add("BFS: Destination achieved in " + std::to_string(current_step + 1) + " steps.", 15);
        if (graph[node_id].get_visited())
            return false; // not wait

        graph[node_id].set_visited(true);
        graph.highlight_node(node_id);

        for (int neighbor : graph[node_id].get_neighbors())
        {
            if (!graph[neighbor].get_visited())
            {
                queue.push(neighbor);
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
