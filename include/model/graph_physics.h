#pragma once

#include <vector>
#include <tuple>
#include <string>

#include "graph_node.h"

namespace mvc
{
    class graph_physics
    {
    private:
        static bool is_paused;

    public:
        /**
         * @brief Returns whether the physical simulation is paused.
         */
        static bool paused();

        /**
         * @brief Toggles physics simulation pause.
         * @return Current simulation state.
         */
        static bool toggle_simulation();

        /**
         * @brief Applies repulsion force between nodes to simulate repulsive behavior.
         * @param nodes Reference to the graph's nodes.
         * @param k_r Repulsion constant.
         */
        static void apply_repulsion(std::vector<graph_node>& nodes, float k_r);
        
        /**
         * @brief Applies attraction force between connected nodes to simulate attractive behavior.
         * @param nodes Reference to the graph's nodes.
         * @param edges Reference to the graph's edges, each represented as a tuple (node1, node2, weight).
         * @param k_a Attraction constant.
         * @param rest_length The rest length of the spring between nodes.
         */
        static void apply_attraction(std::vector<graph_node>& nodes, std::vector<std::tuple<int, int, float>>& edges, float k_a, float rest_length);
        
        /**
         * @brief Applies gravity force to all nodes to simulate gravitational pull.
         * @param nodes Reference to the graph's nodes.
         * @param k_g Gravity constant.
         */
        static void apply_gravity(std::vector<graph_node>& nodes, float k_g);
        
        /**
         * @brief Updates the position and velocity of nodes based on the applied forces.
         * @param nodes Reference to the graph's nodes.
         * @param time_step The time step for the update.
         * @param damping Damping factor to reduce velocity over time.
         */
        static void update_nodes(std::vector<graph_node>& nodes, float time_step, float damping);
        
        /**
         * @brief Applies an explosion force to all nodes to simulate an explosive effect.
         * @param nodes Reference to the graph's nodes.
         * @param explosion_force The magnitude of the explosion force.
         */
        static void explode(std::vector<graph_node>& nodes, float explosion_force);
    };
}
