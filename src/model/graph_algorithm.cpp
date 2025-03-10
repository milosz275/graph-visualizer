#include "graph_algorithm.h"

namespace mvc
{
    graph_algorithm::graph_algorithm() : start_time(std::chrono::steady_clock::now()) {}

    bool graph_algorithm::check_timer()
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
        if (elapsed >= 1) // one second
        {
            start_time = now;
            return true;
        }
        return false;
    }

    void graph_algorithm::fast_forward_timer()
    {
        start_time = std::chrono::steady_clock::now() - std::chrono::seconds(1);
    }
}
