#include "cli.h"

#include <iostream>

#include "graph.h"

using namespace std;

directed_graph g;
graph_node a, b, c, d; // ids 0, 1, 2, 3

void init_example_graph()
{
    // add nodes
    g[a];
    g[b];
    g[c];
    g[d];

    // define edges
    g[a][b] = 5;
    g[a][c] = 3;
    g[b][c] = 2;
    g[b][d] = 2;

    cout << "Generated graph with " << g.get_node_count() << " nodes.\n";
}

void update_graph()
{
    // do nothing
}

void cli_print_graph()
{
    cout << g;
}
