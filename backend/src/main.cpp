#include <iostream>
#include <unistd.h>

// use "g++ -std=c++17 -o graph.out src/main.cpp -DEMSCRIPTEN_GUI=0" to compile for CLI
// use "make" to compile for web (Makefile will use emcc instead of g++)

#if EMSCRIPTEN_GUI == 1

#include <emscripten.h>
#include <emscripten/html5.h>

#include "render.cpp"

void emscripten_loop()
{
    update_graph();
    render();
}

#else

#include "cli.cpp"

void cli_loop()
{
    while (true)
    {
        update_graph();
        cli_print_graph();
        sleep(1);
    }
}

#endif

using namespace std;

int main()
{
#if EMSCRIPTEN_GUI == 1

    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);
    attr.alpha = 0;
    attr.depth = 0;
    attr.stencil = 0;
    attr.antialias = 1;
    attr.majorVersion = 2;

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("#canvas", &attr);
    if (context <= 0)
    {
        cerr << "Failed to create WebGL context!" << '\n';
        return 1;
    }

    emscripten_webgl_make_context_current(context);
    init_gl();

    init_example_graph();
    emscripten_set_main_loop(emscripten_loop, 0, 1);

#else

    init_example_graph();
    cli_loop();

#endif
    return 0;
}
