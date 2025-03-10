#include "dfs_algorithm.h"

namespace mvc
{
    dfs_algorithm::dfs_algorithm(int start_node)
    {
        stack.push(start_node);
    }

    bool dfs_algorithm::step(mvc::graph& graph)
    {
        if (stack.empty())
            return false;

        int node_id = stack.top();
        stack.pop();
        if (graph[node_id].visited)
            return false;

        graph[node_id].visited = true;

        for (int neighbor : graph[node_id].neighbors)
        {
            if (!graph[neighbor].visited)
                stack.push(neighbor);
        }
        return true;
    }

    bool dfs_algorithm::is_complete() const
    {
        return stack.empty();
    }
}
