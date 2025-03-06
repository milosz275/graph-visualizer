#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>

#include "app.h"
#include "renderer.h"
#include "background.h"
#include "text.h"

using namespace std;

void draw_sierpinski_triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, int depth)
{
    if (depth == 0)
        web_ui::renderer::draw_triangle(p1, p2, p3, glm::vec3(1.0f, 1.0f, 1.0f));
    else
    {
        glm::vec2 mid1 = (p1 + p2) / 2.0f;
        glm::vec2 mid2 = (p2 + p3) / 2.0f;
        glm::vec2 mid3 = (p3 + p1) / 2.0f;

        draw_sierpinski_triangle(p1, mid1, mid3, depth - 1);
        draw_sierpinski_triangle(mid1, p2, mid2, depth - 1);
        draw_sierpinski_triangle(mid3, mid2, p3, depth - 1);
    }
}

void render_loop()
{
    web_ui::background::draw_background();
    web_ui::text::clear_text_canvas();
    web_ui::text::draw_text_absolute();

    glm::vec2 p1 = glm::vec2(-0.5f, -0.5f);
    glm::vec2 p2 = glm::vec2(0.5f, -0.5f);
    glm::vec2 p3 = glm::vec2(0.0f, 0.5f);

    draw_sierpinski_triangle(p1, p2, p3, 5);
}

int main()
{
    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);
    attr.alpha = 0;
    attr.depth = 1;
    attr.stencil = 1;
    attr.antialias = 1;
    attr.majorVersion = 2;
    
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("#webglCanvas", &attr);
    if (context <= 0)
    {
        cerr << "Failed to create WebGL context!" << '\n';
        return 1;
    }

    emscripten_webgl_make_context_current(context);

    web_ui::text::setup_canvas();
    web_ui::renderer::init();
    web_ui::app::run(render_loop);

    return 0;
}
