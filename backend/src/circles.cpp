#include <iostream>

#include <GL/gl.h>
#include <GL/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/html5.h>

// Vertex and Fragment Shader sources
const char* vertexShaderSource = R"(
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

const char* fragmentShaderSource = R"(
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

GLuint shaderProgram;
GLuint VBO, VAO;

struct Circle {
    float x, y;      // Position
    float size;      // Size
    float r, g, b;   // Color
};

Circle circles[] = {
    { 0.0f,  0.0f,  50.0f, 1.0f, 0.0f, 0.0f }, // Red circle
    { 0.5f,  0.5f,  30.0f, 0.0f, 1.0f, 0.0f }, // Green circle
    {-0.5f, -0.5f,  40.0f, 0.0f, 0.0f, 1.0f }  // Blue circle
};

void compileShader(GLuint shader, const char* source)
{
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader Compilation Failed:\n" << infoLog << std::endl;
    }
}

void initGL()
{
    // Create and compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShader, vertexShaderSource);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShader, fragmentShaderSource);

    // Link shaders into a program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Clean up shaders as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create and bind a Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and bind a Vertex Buffer Object (VBO)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circles), circles, GL_STATIC_DRAW);

    // Set up vertex attributes
    GLint posAttrib = glGetAttribLocation(shaderProgram, "a_position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Circle), (void*)offsetof(Circle, x));

    GLint sizeAttrib = glGetAttribLocation(shaderProgram, "a_size");
    glEnableVertexAttribArray(sizeAttrib);
    glVertexAttribPointer(sizeAttrib, 1, GL_FLOAT, GL_FALSE, sizeof(Circle), (void*)offsetof(Circle, size));

    GLint colorAttrib = glGetAttribLocation(shaderProgram, "a_color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(Circle), (void*)offsetof(Circle, r));
}

// Main render loop
void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, sizeof(circles) / sizeof(Circle));
}

// WebGL loop function for Emscripten
void mainLoop()
{
    render();
}

// Entry point
int main()
{
    // Create WebGL context
    EmscriptenWebGLContextAttributes attr;
    emscripten_webgl_init_context_attributes(&attr);
    attr.alpha = 0;
    attr.depth = 0;
    attr.stencil = 0;
    attr.antialias = 1;
    attr.majorVersion = 2;

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("#canvas", &attr);
    if (context <= 0)
    {
        std::cerr << "Failed to create WebGL context!" << std::endl;
        return 1;
    }

    emscripten_webgl_make_context_current(context);
    initGL();

    // Run the render loop
    emscripten_set_main_loop(mainLoop, 0, 1);

    return 0;
}
