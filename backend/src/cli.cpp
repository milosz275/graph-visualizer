#include "cli.h"

#include <iostream>

#include "graph.h"

using namespace std;

directed_graph g;
graph_node a, b, c, d; // ids 0, 1, 2, 3

void init_example_graph()
{
    g[a][b] = 5;
    g[a][c] = 3;
    g[b][c] = 2;
    g[b][d] = 2;
    g[c];
    g[d];

    cout << "Generated graph with " << g.get_node_count() << " nodes.\n";
}

void update_graph()
{
    // do nothing
}

void cli_print_graph()
{
    cout << "Graph:\n";
    for (auto& [node, edges] : g)
    {
        cout << node << " -> ";
        for (auto& [target, weight] : edges)
        {
            cout << target << " (" << weight << "), ";
        }
        cout << '\n';
    }
}