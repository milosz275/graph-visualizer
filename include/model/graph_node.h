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
         * 
         */
        graph_node();

        /**
         * 
         */
        graph_node(float x, float y);

        /**
         * 
         */
        graph_node(glm::vec2 position);

        /**
         * 
         */
        bool get_visited();
        
        /**
         * 
         */
        bool set_visited(bool visited);
        
        /**
         * 
         */
        bool set_highlighted(bool highlighted);

        /**
         * 
         */
        int set_parent(int parent);

        /**
         * 
         */
        std::vector<int>& get_neighbors();

        friend class graph;
        friend class graph_physics;
    };
}
