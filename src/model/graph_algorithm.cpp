#include "graph_algorithm.h"

namespace mvc
{
    graph_algorithm::graph_algorithm(std::string label) : label(label), start_time(std::chrono::steady_clock::now()), current_step(0) {}

    std::string graph_algorithm::get_label() { return label; }

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

    int graph_algorithm::get_current_step() { return current_step; }
}
