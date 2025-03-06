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
        static void init();
        static void draw_line(glm::vec2 p1, glm::vec2 p2, glm::vec3 color);
        static void draw_triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec3 color);
        static void draw_rectangle(glm::vec2 p1, glm::vec2 p2, glm::vec3 color);
        static void draw_circle(glm::vec2 center, float radius, glm::vec3 color);
    };
}
