#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

using namespace std;

const char *vertex_shader_source = R"(
    attribute vec2 a_position;
    attribute float a_size;
    attribute vec3 a_color;
    varying vec3 v_color;
    void main() {
        gl_Position = vec4(a_position, 0.0, 1.0);
        gl_PointSize = a_size;
        v_color = a_color;
    }
)";

const char *fragment_shader_source = R"(
    precision mediump float;
    varying vec3 v_color;
    void main() {
        vec2 coord = gl_PointCoord - vec2(0.5);
        if (dot(coord, coord) > 0.25) {
            discard;
        }
        gl_FragColor = vec4(v_color, 1.0);
    }
)";
