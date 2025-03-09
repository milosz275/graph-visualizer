#include "background.h"

#include <GLES3/gl3.h>

namespace web_ui
{
    void background::draw_background()
    {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
