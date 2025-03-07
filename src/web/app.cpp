#include "app.h"

using namespace std;

namespace web_ui
{
    function<void()> global_loop;

    void main_loop_wrapper()
    {
        if (global_loop)
            global_loop();
    }

    void app::run(function<void()> loop)
    {
        global_loop = loop;
        emscripten_set_main_loop(main_loop_wrapper, 0, 1);
    }

    void app::cleanup(function<void()> clean)
    {
        clean();
    }
}
