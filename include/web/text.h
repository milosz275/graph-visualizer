#pragma once

#include <string>
#include <GLES3/gl3.h>
#include <glm/vec2.hpp>

namespace web_ui
{
    class text
    {
    public:
        /**
         * @brief Setups text canvas.
         */
        static void setup_canvas();

        /**
         * @brief Draws text wrapping Emscripten.
         * @details Supply (x, y) coordinates, text style to draw it on text canvas.
         * @param x Coordinate x in (-1.0f, 1.0f) domain, where (0, 0) is center
         * @param y Coordinate y in (-1.0f, 1.0f) domain, where (0, 0) is center
         * @param text String text to be drawn
         * @param font String font style, e.g. "30px Arial"
         * @param fill_style String fill style, e.g. "white"
         */
        static void draw_text(glm::vec2 coords = {-0.9f, 0.9f}, std::string text = "Graph Visualizer", std::string font = "30px serif", std::string fill_style = "white");
        
        /**
         * @brief Draws text wrapping Emscripten.
         * @details Supply (x, y) coordinates, text style to draw it on text canvas.
         * @param x Coordinate x absolute in window resolution, where (0, 0) is upper-left corner
         * @param y Coordinate y absolute in window resolution, where (0, 0) is upper-left corner
         * @param text String text to be drawn
         * @param font String font style, e.g. "30px Arial"
         * @param fill_style String fill style, e.g. "white"
         */
        static void draw_text_absolute(glm::vec2 coords = {10.0f, 10.0f}, std::string text = "Graph Visualizer", std::string font = "30px serif", std::string fill_style = "white");

        /**
         * @brief Clears text canvas.
         * @details Prevents overlapping of printed text.
         * @attention Must be runned before any text that will be printed in each cycle.
         */
        static void clear_text_canvas();
    };
}
