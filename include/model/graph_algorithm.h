#pragma once

#include <chrono>

#include "graph.h"

namespace mvc
{
    class graph_algorithm
    {
    protected:
        std::string label;
        int start_node;
        std::chrono::steady_clock::time_point start_time;
        int current_step;
        double step_pause;
        int step_index; // 

        /**
         * @brief Updates step_pause using step_index.
         *
         * 2^step_index = step_pause (..., 1/4, 1/2, 1, 2, 4, ...)
         *
         * @return Value of newly set step pause value.
         */
        double update_step_pause();

    public:
        /**
         * @brief Provides base to extend with specialized algorithms.
         * @note Creation of graph_algorithm objects is not allowed.
         * @param label Graph label.
         * @param start_node Starting node id.
         */
        graph_algorithm(std::string label, int start_node);

        /**
         * @brief Destructor.
         */
        virtual ~graph_algorithm() = default;

        /**
         * @brief Returns algorithm label
         * @return Graph label.
         */
        virtual std::string get_label();

        /**
         * @brief Allows to be overloaded step of the derived algorithm.
         * @param graph Graph reference
         * @return Return true if waiting after print is advised, false when the step was empty (no changes to data structures).
         */
        virtual bool step(mvc::graph& graph) = 0;

        /**
         * @brief Allows to be overloaded check of algorithm's completion.
         * @return Return true if algorithm is complete, false otherwise.
         */
        virtual bool is_complete() const = 0;

        /**
         * @brief Returns whether timer was resetted before one second earlier.
         */
        bool check_timer();

        /**
         * @brief Skips time in the timer to older than one second (skip waiting).
         */
        void fast_forward_timer();

        /**
         * @brief Gets current algorithm step id.
         * @return Returns current step's id.
         */
        int get_current_step();

        /**
         * @brief Decrements step index. Speeds up simulation by recalculating step pause.
         * @return Newly set step pause.
         */
        float speed_up();

        /**
         * @brief Increments step index. Slows down simulation by recalculating step pause.
         * @return Newly set step pause.
         */
        float slow_down();
    };
}
