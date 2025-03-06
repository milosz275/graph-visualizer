#pragma once

#include <vector>

#include <glm/glm.hpp> // handling positions and transformations
#include <GLES3/gl3.h>

namespace web_ui
{
    class renderer
    {
    private:
        static GLint program;
        static int canvas_width;
        static int canvas_height;
    
    public:
        /**
         * @brief Initializes the renderer.
         * @attention Run once before drawing any shapes.
         */
        static void init();

        /**
         * @brief Draws line connect two points with specified color.
         * @param p1 First point (x, y)
         * @param p2 Second point (x, y)
         * @param color Color vector (R, G, B)
         */
        
         /**
         * @brief Draws a line connecting two points with the specified color.
         * @param p1 First point (x, y)
         * @param p2 Second point (x, y)
         * @param color Color vector (R, G, B)
         */
        static void draw_line(glm::vec2 p1, glm::vec2 p2, glm::vec3 color);

        /**
         * @brief Draws a triangle connecting three points with the specified color.
         * @param p1 First point (x, y)
         * @param p2 Second point (x, y)
         * @param p3 Third point (x, y)
         * @param color Color vector (R, G, B)
         */
        static void draw_triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec3 color);

        /**
         * @brief Draws a rectangle defined by two opposite corners with the specified color.
         * @param p1 First corner point (x, y)
         * @param p2 Opposite corner point (x, y)
         * @param color Color vector (R, G, B)
         */
        static void draw_rectangle(glm::vec2 p1, glm::vec2 p2, glm::vec3 color);

        /**
         * @brief Draws a circle with the specified center, radius, and color.
         * @param center Center point of the circle (x, y)
         * @param radius Radius of the circle
         * @param color Color vector (R, G, B)
         */
        static void draw_circle(glm::vec2 center, float radius, glm::vec3 color);

        /**
         * @brief Draws an ellipse with the specified center, radii, and color.
         * @param center Center point of the ellipse (x, y)
         * @param radius_x Radius of the ellipse along the x-axis
         * @param radius_y Radius of the ellipse along the y-axis
         * @param color Color vector (R, G, B)
         */
        static void draw_ellipse(glm::vec2 center, float radius_x, float radius_y, glm::vec3 color);
    };
}
