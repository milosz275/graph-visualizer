#include "graph_algorithm.h"

#include <iostream>

namespace mvc
{
    graph_algorithm::graph_algorithm(std::string label, int start_node)
        : label(label), start_node(start_node), start_time(std::chrono::steady_clock::now()), current_step(0), step_index(0)
    {
        update_step_pause();
    }

    double graph_algorithm::update_step_pause()
    {
        step_pause = std::pow(2, step_index);
        return step_pause;
    }

    std::string graph_algorithm::get_label() { return label; }

    bool graph_algorithm::check_timer()
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(now - start_time).count(); // Use double for fractional seconds
        if (elapsed >= step_pause)
        {
            start_time = now;
            return true;
        }
        return false;
    }

    void graph_algorithm::fast_forward_timer()
    {
        if (step_pause < 1.0f)
            start_time = std::chrono::steady_clock::now() - std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>(step_pause));
        else
            start_time = std::chrono::steady_clock::now() - std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>(step_pause + 1.0));
    }

    int graph_algorithm::get_current_step() { return current_step; }

    float graph_algorithm::speed_up()
    {
        step_index--;
        return (float)update_step_pause();
    }

    float graph_algorithm::slow_down()
    {
        step_index++;
        return (float)update_step_pause();
    }
}
