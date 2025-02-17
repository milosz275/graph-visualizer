#include "shader.h"

#include <iostream>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>

using namespace std;

void compile_shader(GLuint shader, const char *source)
{
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        cerr << "Shader Compilation Failed:\n"
             << info_log << '\n';
    }
}

const char *circle_vertex_shader_source = R"(
    attribute vec2 a_position;
    attribute float a_size;
    attribute vec3 a_color;
    varying vec3 v_color;
    void main()
    {
        gl_Position = vec4(a_position, 0.0, 1.0);
        gl_PointSize = a_size;
        v_color = a_color;
    }
)";

const char *circle_fragment_shader_source = R"(
    precision mediump float;
    varying vec3 v_color;
    void main()
    {
        vec2 coord = gl_PointCoord - vec2(0.5);
        if (dot(coord, coord) > 0.25)
        {
            discard;
        }
        gl_FragColor = vec4(v_color, 1.0);
    }
)";

const char *line_vertex_shader_source = R"(
    attribute vec2 a_position;
    attribute vec3 a_color;
    varying vec3 v_color;
    void main()
    {
        gl_Position = vec4(a_position, 0.0, 1.0);
        v_color = a_color;
    }
)";

const char *line_fragment_shader_source = R"(
    precision mediump float;
    varying vec3 v_color;
    void main()
    {
        gl_FragColor = vec4(v_color, 1.0);
    }
)";
