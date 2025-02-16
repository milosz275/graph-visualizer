#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>

#include "shader.cpp"

using namespace std;

GLuint shader_program;
GLuint VBO, VAO;

static int canvas_width;
static int canvas_height;

struct background
{
    enum Mode
    {
        WHITE,
        DARK
    };

    Mode mode;
    float white_rgb[3];
    float dark_rgb[3];

    background()
    {
        mode = DARK; // default color mode

        white_rgb[0] = 0.9f;
        white_rgb[1] = 0.9f;
        white_rgb[2] = 0.9f;

        dark_rgb[0] = 0.0f;
        dark_rgb[1] = 0.1f;
        dark_rgb[2] = 0.2f;
    }

    void set_mode(Mode new_mode) { mode = new_mode; }
    const float *get_current_rgb() const { return (mode == WHITE) ? white_rgb : dark_rgb; }
};

background bg;

struct circle
{
    float x, y;
    float size;
    float r, g, b;
};

circle circles[] =
    {
        {0.0f, 0.0f, 50.0f, 1.0f, 0.0f, 0.0f},   // Red circle
        {0.5f, 0.5f, 30.0f, 0.0f, 1.0f, 0.0f},   // Green circle
        {-0.5f, -0.5f, 40.0f, 0.0f, 0.0f, 1.0f}, // Blue circle
        {-0.5f, 0.5f, 60.0f, 0.9f, 0.9f, 0.0f},  // Yellow circle
        {0.5f, -0.5f, 70.0f, 0.9f, 0.0f, 0.9f}   // Purple circle
};

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

void init_gl()
{
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    compile_shader(vertex_shader, vertex_shader_source);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    compile_shader(fragment_shader, fragment_shader_source);

    // Link shaders into a program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // Check for linking errors
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        cerr << "Shader Program Linking Failed:\n"
             << info_log << '\n';
    }

    // Clean up shaders as they are no longer needed
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Create and bind a Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and bind a Vertex Buffer Object (VBO)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circles), circles, GL_STATIC_DRAW);

    // Set up vertex attributes
    GLint pos_attrib = glGetAttribLocation(shader_program, "a_position");
    glEnableVertexAttribArray(pos_attrib);
    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, sizeof(circle), (void *)offsetof(circle, x));

    GLint size_attrib = glGetAttribLocation(shader_program, "a_size");
    glEnableVertexAttribArray(size_attrib);
    glVertexAttribPointer(size_attrib, 1, GL_FLOAT, GL_FALSE, sizeof(circle), (void *)offsetof(circle, size));

    GLint color_attrib = glGetAttribLocation(shader_program, "a_color");
    glEnableVertexAttribArray(color_attrib);
    glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(circle), (void *)offsetof(circle, r));

    // Save canvas size
    canvas_width = EM_ASM_INT({ return getCanvasSize().width; }, 0);
    canvas_height = EM_ASM_INT({ return getCanvasSize().height; }, 0);
    cout << "width: " << canvas_width << '\n';
    cout << "height: " << canvas_height << '\n';
}

void render()
{
    const float *rgb = bg.get_current_rgb();
    glClearColor(rgb[0], rgb[1], rgb[2], 1.0f); // background
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, sizeof(circles) / sizeof(circle));
}
