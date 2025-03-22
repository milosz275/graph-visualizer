#include "background.h"

#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

namespace web_ui
{
    int background::darkmode;

    bool background::toggle_darkmode()
    {
        int result = {EM_ASM_INT({ return toggleDarkmode(); }, 0)};
        if (result)
            return true;
        else
            return false;
    }

    bool background::get_darkmode()
    {
        int result = {EM_ASM_INT({ return getDarkmode(); }, 0)};
        if (result)
            return true;
        else
            return false;
    }

    void background::draw_background()
    {
        darkmode = {EM_ASM_INT({ return getDarkmode(); }, 0)};

        if (!darkmode)
            glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
        else
            glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);
    }
}
