#include "dfs_algorithm.h"

#include "notifications.h"

namespace mvc
{
    dfs_algorithm::dfs_algorithm(int start_node) : graph_algorithm("DFS", start_node)
    {
        stack.push(start_node);
    }

    bool dfs_algorithm::step(mvc::graph& graph)
    {
        if (stack.empty())
            return false; // not wait

        int node_id = stack.top();
        stack.pop();
        if (graph[node_id].get_visited())
            return false; // not wait
        if (node_id == graph.get_node_count() - 1) // assuming target is last
            web_ui::notifications::add("DFS: Destination achieved in " + std::to_string(current_step + 1) + " steps.", 15);

        graph[node_id].set_visited(true);
        graph.highlight_node(node_id);

        for (int neighbor : graph[node_id].get_neighbors())
        {
            if (!graph[neighbor].get_visited())
                stack.push(neighbor);
        }
        current_step++;
        return true; // wait
    }

    bool dfs_algorithm::is_complete() const
    {
        return stack.empty();
    }
}
