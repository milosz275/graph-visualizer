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

GLuint circle_shader_program;  // shader program for circles
GLuint edge_shader_program;    // shader program for edges
GLuint circle_vbo, circle_vao; // vertex buffer object, vertex array object for circles
GLuint edge_vbo, edge_vao;     // vertex buffer object, vertex array object for edges

static int canvas_width, canvas_height; // canvas resolution

unordered_map<int, pair<float, float>> node_positions; // node id -> (x, y)

background::background()
{
    mode = LIGHT; // default color mode

    light_rgb[0] = 0.9f;
    light_rgb[1] = 0.9f;
    light_rgb[2] = 1.0f;

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
    return (mode == LIGHT) ? light_rgb : dark_rgb;
}

background bg;

directed_graph g;
graph_node a, b, c, d; // ids 0, 1, 2, 3

void init_example_graph()
{
    // add nodes
    g[a];
    g[b];
    g[c];
    g[d];

    // define edges
    g[a][b] = 5; // 0 to 1
    g[a][c] = 3; // 0 to 2
    g[b][c] = 2; // 1 to 2
    g[b][d] = 2; // 1 to 3

    cout << "Generated graph with " << g.get_node_count() << " nodes and " << g.get_edge_count() << " edges.\n";
    cout << g;
}

vector<float> generate_circle_render_data()
{
    vector<float> data;

    // grid layout - no resolution screen resolution independence (scaling)
    int rows = 2, cols = 2;
    int i = 0, j = 0;
    float inc = 0.5f;

    g.iterate_nodes_by_id([&data, &rows, &cols, &i, &j, &inc](graph_node &node)
                    {
        circle c;
        c.x = -0.25f + i * inc;       // from left to right
        c.y = 0.25f + j * (-1 * inc); // from top to bottom
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
        node_positions[node.get_id()] = {c.x, c.y};
        i++; 
        if (i == cols)
        {
            i = 0;
            j++;
            if (j == rows)
                j = 0;
        } });

    return data;
}

vector<float> generate_edge_render_data()
{
    vector<float> data;

    g.iterate_edges([&data](const graph_node &start, const graph_node &end)
                    {
                        auto start_pos = node_positions[start.get_id()];
                        auto end_pos = node_positions[end.get_id()];

                        // first vertex of the edge
                        data.push_back(start_pos.first);
                        data.push_back(start_pos.second);
                        data.push_back(end_pos.first);
                        data.push_back(end_pos.second);
                        data.push_back(1.0f); // r
                        data.push_back(1.0f); // g
                        data.push_back(1.0f); // b

                        // second vertex of the edge
                        data.push_back(end_pos.first);
                        data.push_back(end_pos.second);
                        data.push_back(start_pos.first);
                        data.push_back(start_pos.second);
                        data.push_back(1.0f); // r
                        data.push_back(1.0f); // g
                        data.push_back(1.0f); // b
                    });

    return data;
}

void init_gl()
{
    // compile and link circle shaders
    GLuint circle_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    compile_shader(circle_vertex_shader, circle_vertex_shader_source);

    GLuint circle_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    compile_shader(circle_fragment_shader, circle_fragment_shader_source);

    circle_shader_program = glCreateProgram();
    glAttachShader(circle_shader_program, circle_vertex_shader);
    glAttachShader(circle_shader_program, circle_fragment_shader);
    glLinkProgram(circle_shader_program);

    // check for linking errors
    GLint success;
    glGetProgramiv(circle_shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(circle_shader_program, 512, NULL, info_log);
        cerr << "Circle Shader Program Linking Failed:\n"
             << info_log << '\n';
    }

    // compile and link edge shaders
    GLuint edge_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    compile_shader(edge_vertex_shader, edge_vertex_shader_source);

    GLuint edge_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    compile_shader(edge_fragment_shader, edge_fragment_shader_source);

    edge_shader_program = glCreateProgram();
    glAttachShader(edge_shader_program, edge_vertex_shader);
    glAttachShader(edge_shader_program, edge_fragment_shader);
    glLinkProgram(edge_shader_program);

    // check for linking errors
    glGetProgramiv(edge_shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info_log[512];
        glGetProgramInfoLog(edge_shader_program, 512, NULL, info_log);
        cerr << "Edge Shader Program Linking Failed:\n"
             << info_log << '\n';
    }

    // generate buffer data from graph
    vector<float> node_data = generate_circle_render_data();
    vector<float> edge_data = generate_edge_render_data();

    // clean up shaders as they are no longer needed
    glDeleteShader(circle_vertex_shader);
    glDeleteShader(circle_fragment_shader);
    glDeleteShader(edge_vertex_shader);
    glDeleteShader(edge_fragment_shader);

    // create and bind a Vertex Array Object (VAO) for nodes
    glGenVertexArrays(1, &circle_vao);
    glBindVertexArray(circle_vao);

    // create and bind a Vertex Buffer Object (VBO) for nodes
    glGenBuffers(1, &circle_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
    glBufferData(GL_ARRAY_BUFFER, node_data.size() * sizeof(float), node_data.data(), GL_STATIC_DRAW);

    // set up vertex attributes for nodes
    GLint pos_attrib = glGetAttribLocation(circle_shader_program, "a_position");
    if (pos_attrib != -1)
    {
        glEnableVertexAttribArray(pos_attrib);
        glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    }

    GLint size_attrib = glGetAttribLocation(circle_shader_program, "a_size");
    if (size_attrib != -1)
    {
        glEnableVertexAttribArray(size_attrib);
        glVertexAttribPointer(size_attrib, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(2 * sizeof(float)));
    }

    GLint color_attrib = glGetAttribLocation(circle_shader_program, "a_color");
    if (color_attrib != -1)
    {
        glEnableVertexAttribArray(color_attrib);
        glVertexAttribPointer(color_attrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    }

    // create and bind a Vertex Array Object (VAO) for edges
    glGenVertexArrays(1, &edge_vao);
    glBindVertexArray(edge_vao);

    // create and bind a Vertex Buffer Object (VBO) for edges
    glGenBuffers(1, &edge_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, edge_vbo);
    glBufferData(GL_ARRAY_BUFFER, edge_data.size() * sizeof(float), edge_data.data(), GL_STATIC_DRAW);

    // setup attribute
    pos_attrib = glGetAttribLocation(edge_shader_program, "a_position");
    if (pos_attrib != -1)
    {
        glEnableVertexAttribArray(pos_attrib);
        glVertexAttribPointer(pos_attrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
    }

    GLint color_attrib_edge = glGetAttribLocation(edge_shader_program, "a_color");
    if (color_attrib_edge != -1)
    {
        glEnableVertexAttribArray(color_attrib_edge);
        glVertexAttribPointer(color_attrib_edge, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(4 * sizeof(float)));
    }

    // save canvas size
    canvas_width = EM_ASM_INT({ return getCanvasSize().width; }, 0);
    canvas_height = EM_ASM_INT({ return getCanvasSize().height; }, 0);
    cout << "Canvas resolution: " << canvas_width << "x" << canvas_height << '\n';
}

void update_graph()
{
    vector<float> circle_data = generate_circle_render_data();

    glBindBuffer(GL_ARRAY_BUFFER, circle_vbo);
    glBufferData(GL_ARRAY_BUFFER, circle_data.size() * sizeof(float), circle_data.data(), GL_STATIC_DRAW);

    vector<float> edge_data = generate_edge_render_data();

    glBindBuffer(GL_ARRAY_BUFFER, edge_vbo);
    glBufferData(GL_ARRAY_BUFFER, edge_data.size() * sizeof(float), edge_data.data(), GL_STATIC_DRAW);
}

void render()
{
    const float *rgb = bg.get_current_rgb();
    glClearColor(rgb[0], rgb[1], rgb[2], 1.0f); // background
    glClear(GL_COLOR_BUFFER_BIT);

    // draw nodes
    glUseProgram(circle_shader_program);
    glBindVertexArray(circle_vao);
    glDrawArrays(GL_POINTS, 0, g.get_node_count());

    // draw edges
    glUseProgram(edge_shader_program);
    glBindVertexArray(edge_vao);
    glDrawArrays(GL_LINES, 0, g.get_edge_count() * 2);
}
