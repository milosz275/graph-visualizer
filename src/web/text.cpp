#include "text.h"

#include <iostream> // remove
#include <algorithm>

#include <emscripten.h>
#include <emscripten/html5.h>

#include <glm/vec2.hpp>

#include "canvas.h"

namespace web_ui
{
    // javascript macro to setup canvas using emscripten
    EM_JS(void, em_setup_canvas, (), {
        var glCanvas = document.getElementById('webglCanvas');
        var textCanvas = document.getElementById('textCanvas');
        
        if (!glCanvas || !textCanvas) {
            console.error("Canvas elements not found!");
            return;
        }
    
        glCanvas.width = textCanvas.width = window.innerWidth;
        glCanvas.height = textCanvas.height = window.innerHeight;
    
        Module.textCanvas = textCanvas;
    });
    
    // javascript macro to render text using emscripten
    EM_JS(void, em_render_text, (float x, float y, const char* text, const char* font, const char* fill_style), {
        var textCanvas = Module.textCanvas;
        if (!textCanvas) {
            console.error("Text canvas is not initialized.");
            return;
        }
        
        var ctx = textCanvas.getContext('2d');
        if (!ctx) {
            console.error("2D context is not available.");
            return;
        }

        ctx.font = UTF8ToString(font);
        ctx.fillStyle = UTF8ToString(fill_style);
        ctx.fillText(UTF8ToString(text), x, y);
    });

    // javascript macro to clear text canvas using emscripten
    EM_JS(void, em_clear_text_canvas, (), {
        var textCanvas = Module.textCanvas;
        if (!textCanvas) {
            console.error("Text canvas is not initialized.");
            return;
        }
        
        var ctx = textCanvas.getContext('2d');
        if (!ctx) {
            console.error("2D context is not available.");
            return;
        }
    
        ctx.clearRect(0, 0, textCanvas.width, textCanvas.height);
    });

    void text::setup_canvas()
    {
        em_setup_canvas();
    }

    void text::draw_text(glm::vec2 coords, std::string text, std::string font, std::string fill_style)
    {
        glm::vec2 canvas = web_ui::canvas::get_canvas_size();
        float pixel_x = (coords.x + 1.0f) * 0.5f * canvas.x;
        float pixel_y = (1.0f - coords.y) * 0.5f * canvas.y;
        
        // parsing font style
        if ((int)font.length() < 4)
            font = "2px Arial";
        else if (isdigit(font[0]) && isdigit(font[1]) && isdigit(font[2]))
            font = "64px Arial";
        else if (isdigit(font[0]) && isdigit(font[1]))
        {
            if ((float)canvas.x / (float)canvas.y < 4.0 / 3.0)
            {
                int font_size = std::stoi(font.substr(0, 2));
                font_size *= (canvas.x / 1000);
                font = std::to_string(font_size) + "px Arial";
            }
        }
        else
            font = "8px Arial";

        // parsing fill style
        if (!std::all_of(fill_style.begin(), fill_style.end(), [](char c) { return std::isalpha(c); }))
            fill_style = "red";

        em_render_text(pixel_x, pixel_y, text.c_str(), font.c_str(), fill_style.c_str());
    }

    void text::draw_text_absolute(glm::vec2 coords, std::string text, std::string font, std::string fill_style)
    {
        float pixel_x = coords.x;
        float pixel_y = coords.y;
        // [ ] Load actual size instead of 10-99 formatted size (e.g. "12px Arial" but not "2px Arial")
        if (isdigit(font[0]) && isdigit(font[1]))
            pixel_y += std::stoi(font.substr(0, 2));
        em_render_text(pixel_x, pixel_y, text.c_str(), font.c_str(), fill_style.c_str());
    }

    void text::clear_text_canvas()
    {
        em_clear_text_canvas();
    }
}
