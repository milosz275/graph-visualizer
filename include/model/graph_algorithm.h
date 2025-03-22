#pragma once

#include <chrono>

#include "graph.h"

namespace mvc
{
    class graph_algorithm
    {
    protected:
        std::string label;
        std::chrono::steady_clock::time_point start_time;

    public:
        /**
         * @brief Provides base to extend with specilized algorithms.
         * @note Creation of graph_algorithm objects is not allowed.
         */
        graph_algorithm(std::string label);

        /**
         * @brief Destructor.
         */
        virtual ~graph_algorithm() = default;

        /**
         * @brief Returns algorithm label
         */
        virtual std::string get_label();

        /**
         * @brief Allows to be overloaded step of the derived algorithm.
         * @param graph Graph reference
         * @return Return true if waiting after print is adviced, false when the step was empty (no changes to data structures).
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
    };
}
