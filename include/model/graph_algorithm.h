#pragma once

#include <queue>
#include <set>

#include "graph.h"

namespace mvc
{
    class graph_algorithm
    {
    public:
        virtual ~graph_algorithm() = default;
        virtual void step(mvc::graph& graph) = 0;
        virtual bool is_complete() const = 0;
    };
    
    // BFS (colors nodes while running)
    class bfs_algorithm : public graph_algorithm
    {
    private:
        std::queue<int> queue;
        std::set<int> visited;
    public:
        void step(mvc::graph& graph) override;
        bool is_complete() const override;
    };
}
