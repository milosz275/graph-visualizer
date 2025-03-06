#pragma once

#include <functional>

#include <emscripten/html5.h>

namespace web_ui
{
    class app
    {
    public:
        static void run(std::function<void()> loop);
        static void cleanup(std::function<void()> clean);
    };
}
