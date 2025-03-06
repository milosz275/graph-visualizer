#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include "app.h"
#include "renderer.h"
#include "background.h"
#include "text.h"

using namespace std;

void render_loop()
{
    // drawing
    web_ui::background::draw_background();
    web_ui::renderer::draw_circle({0.75f, 0.75f}, 0.200f, {1, 0.80f, 0}); // sun
    web_ui::renderer::draw_circle({0.75f, 0.75f}, 0.175f, {1, 0.90f, 0}); // sun
    web_ui::renderer::draw_circle({0.75f, 0.75f}, 0.150f, {1, 1.00f, 0}); // sun
    web_ui::renderer::draw_rectangle({-0.5f, -0.5f}, {0.5, 0.25f}, {0.8f, 0.5f, 0.2f}); // house base
    web_ui::renderer::draw_triangle({-0.75f, 0.25f}, {0.75f, 0.25f}, {0.0f, 0.75f}, {0.6f, 0.3f, 0.1f}); // roof
    web_ui::renderer::draw_rectangle({-0.1f, -0.5f}, {0.1f, 0.0f}, {0.4f, 0.2f, 0.1f}); // door
    web_ui::renderer::draw_rectangle({-0.4f, -0.2f}, {-0.2f, 0.0f}, {0.7f, 0.9f, 1.0f}); // left window
    web_ui::renderer::draw_rectangle({0.2f, -0.2f}, {0.4f, 0.0f}, {0.7f, 0.9f, 1.0f}); // right window
    web_ui::renderer::draw_line({-0.4f, -0.1f}, {-0.2f, -0.1f}, {0, 0, 0}); // left window horizontal window pane
    web_ui::renderer::draw_line({-0.3f, -0.2f}, {-0.3f, 0.0f}, {0, 0, 0}); // left window vertical window pane
    web_ui::renderer::draw_line({0.2f, -0.1f}, {0.4f, -0.1f}, {0, 0, 0}); // right window horizontal window pane
    web_ui::renderer::draw_line({0.3f, -0.2f}, {0.3f, 0.0f}, {0, 0, 0}); // right window vertical window pane

    // text
    web_ui::text::clear_text_canvas();
    web_ui::text::draw_text_absolute();
    web_ui::text::draw_text({-0.03f, -0.75f}, "House", "20px serif", "brown");
}

int main()
{
    web_ui::text::setup_canvas();

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

    web_ui::renderer::init();
    web_ui::app::run(render_loop);

    return 0;
}
