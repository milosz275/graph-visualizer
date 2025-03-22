#include "dfs_algorithm.h"

namespace mvc
{
    dfs_algorithm::dfs_algorithm(int start_node) : graph_algorithm("DFS")
    {
        stack.push(start_node);
    }

    bool dfs_algorithm::step(mvc::graph& graph)
    {
        if (stack.empty())
            return false;

        int node_id = stack.top();
        stack.pop();
        if (graph[node_id].get_visited())
            return false;

        graph[node_id].set_visited(true);
        graph.highlight_node(node_id);

        for (int neighbor : graph[node_id].get_neighbors())
        {
            if (!graph[neighbor].get_visited())
                stack.push(neighbor);
        }
        return true;
    }

    bool dfs_algorithm::is_complete() const
    {
        return stack.empty();
    }
}
