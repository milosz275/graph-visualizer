#pragma once

#include <vector>
#include <cmath>

#include <glm/vec2.hpp>

namespace mvc
{
    class graph;
    class graph_physics;

    class graph_node
    {
        static int node_counter;
        int id;
        
        glm::vec2 position;
        glm::vec2 velocity;
        glm::vec2 force_accumulator;
        
        std::vector<int> neighbors;
        bool visited;
        bool highlighted;
        int parent;

    public:
        /**
         * @brief Creates default graph node.
         */
        graph_node();

        /**
         * @brief Creates node at specific coordinates.
         * @param x Coordinate x.
         * @param y Coordinate y.
         */
        graph_node(float x, float y);

        /**
         * @brief Creates node at specific coordinates.
         * @param position Position coordinates.
         */
        graph_node(glm::vec2 position);

        /**
         * @brief Checks if the node is visited.
         * @return Returns visited flag.
         */
        bool get_visited();
        
        /**
         * @brief Sets the node's visited flag.
         * @return Returns visited flag.
         */
        bool set_visited(bool visited);
        
        /**
         * @brief Sets the node's highlighted flag.
         * @return Returns highlighted flag.
         */
        bool set_highlighted(bool highlighted);

        /**
         * @brief Sets the node's parent id.
         * @return Returns set parent.
         */
        int set_parent(int parent);

        /**
         * @brief Returns node's neighbors vector.
         */
        std::vector<int>& get_neighbors();

        friend class graph;
        friend class graph_physics;
    };
}
