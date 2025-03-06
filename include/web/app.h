#pragma once

#include <functional>

#include <emscripten/html5.h>

namespace web_ui
{
    class app
    {
    public:
        /**
         * @brief Connect loop cycle function to run by Emcripten in main loop
         */
        static void run(std::function<void()> loop);

        /**
         * @brief Connect cleanup function to run by Emcripten after main loop
         */
        static void cleanup(std::function<void()> clean);
    };
}
