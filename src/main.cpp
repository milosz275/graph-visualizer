#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

#include "app.h"

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
        std::cerr << "Failed to create WebGL context!" << '\n';
        return 1;
    }
    emscripten_webgl_make_context_current(context);

    app::graph_app::run();

    return 0;
}
