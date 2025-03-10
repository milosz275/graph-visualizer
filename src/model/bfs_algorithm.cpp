#include "bfs_algorithm.h"

namespace mvc
{
    bfs_algorithm::bfs_algorithm(int start_node)
    {
        queue.push(start_node);
    }

    bool bfs_algorithm::step(mvc::graph& graph)
    {
        if (queue.empty())
            return false;

        int node_id = queue.front();
        queue.pop();
        if (graph[node_id].visited)
            return false;

        graph[node_id].visited = true;

        for (int neighbor : graph[node_id].neighbors)
        {
            if (!graph[neighbor].visited)
            {
                queue.push(neighbor);
                graph[neighbor].parent = node_id;
            }
        }
        return true;
    }

    bool bfs_algorithm::is_complete() const
    {
        return queue.empty();
    }
}
