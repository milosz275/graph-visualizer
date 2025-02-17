#include "render.h"

#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>

#include "shader.cpp"
#include "graph.cpp"

using namespace std;

GLuint shader_program;
GLuint VBO, VAO;

static int canvas_width;
static int canvas_height;

background::background()
{
    mode = DARK; // default color mode

    white_rgb[0] = 0.9f;
    white_rgb[1] = 0.9f;
    white_rgb[2] = 0.9f;

    dark_rgb[0] = 0.0f;
    dark_rgb[1] = 0.1f;
    dark_rgb[2] = 0.2f;
}

void background::set_mode(Mode new_mode)
{
    mode = new_mode;
}

const float *background::get_current_rgb() const
{
    return (mode == WHITE) ? white_rgb : dark_rgb;
}

background bg;

directed_graph g;
graph_node a, b, c, d, e; // ids 0, 1, 2, 3, 4

void init_example_graph()
{
    g[a][b] = 5;
    g[a][c] = 3;
    g[b][c] = 2;
    g[b][d] = 2;
    g[c];
    g[d];
    g[e];

    cout << "Generated graph with " << g.get_node_count() << " nodes.\n";
}

vector<float> generate_circle_render_data()
{
    vector<float> data;

    // grid layout - no resolution screen resolution independence (scaling)
    int rows = 2, cols = 2;
    int i = 0, j = 0;
    float inc = 0.5f;

    g.iterate_nodes_once([&data, &rows, &cols, &i, &j, &inc](const graph_node &node)
                         {
        circle c;
        c.x = -0.25f + i * inc;
        c.y = -0.25f + j * inc;
        c.size = 40.0f;
        c.r = 1.0f;
        c.g = 0.0f;
        c.b = 1.0f;
        data.push_back(c.x);
        data.push_back(c.y);
        data.push_back(c.size);
        data.push_back(c.r);
        data.push_back(c.g);
        data.push_back(c.b);
        i++; 
        if (i == cols)
        {
            i = 0;
            j++;
        }
    });

    return data;
}

void init_gl()
{
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    compile_shader(vertex_shader, vertex_shader_source);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    compile_shader(fragment_shader, fragment_shader_source);

    // link shaders into a program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // check for linking errors
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        cerr << "Shader Program Linking Failed:\n"
             << info_log << '\n';
    }

    // generate buffer data from graph
    vector<float> data = generate_circle_render_data();

    // clean up shaders as they are no longer needed
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // create and bind a Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // create and bind a Vertex Buffer Object (VBO)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    // set up vertex attributes
    GLint pos_attrib = glGetAttribLocation(shader_program, "a_position");
    glEnableVertexAttribArray(pos_attrib);
    glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, sizeof(circle), (void *)offsetof(circle, x));

    GLint size_attrib = glGetAttribLocation(shader_program, "a_size");
    glEnableVertexAttribArray(size_attrib);
    glVertexAttribPointer(size_attrib, 1, GL_FLOAT, GL_FALSE, sizeof(circle), (void *)offsetof(circle, size));

    GLint color_attrib = glGetAttribLocation(shader_program, "a_color");
    glEnableVertexAttribArray(color_attrib);
    glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(circle), (void *)offsetof(circle, r));

    // save canvas size
    canvas_width = EM_ASM_INT({ return getCanvasSize().width; }, 0);
    canvas_height = EM_ASM_INT({ return getCanvasSize().height; }, 0);
    cout << "Canvas resolution: " << canvas_width << "x" << canvas_height << '\n';
}

void update_graph()
{
    vector<float> data = generate_circle_render_data();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
}

void render()
{
    const float *rgb = bg.get_current_rgb();
    glClearColor(rgb[0], rgb[1], rgb[2], 1.0f); // background
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, g.get_node_count());
}
