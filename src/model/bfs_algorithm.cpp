#include "bfs_algorithm.h"

namespace mvc
{
    bfs_algorithm::bfs_algorithm(int start_node) : graph_algorithm("BFS")
    {
        queue.push(start_node);
    }

    bool bfs_algorithm::step(mvc::graph& graph)
    {
        if (queue.empty())
            return false;

        int node_id = queue.front();
        queue.pop();
        if (graph[node_id].get_visited())
            return false;

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
        return true;
    }

    bool bfs_algorithm::is_complete() const
    {
        return queue.empty();
    }
}
