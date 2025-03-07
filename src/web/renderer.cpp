#include "renderer.h"

#include <iostream>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>

using namespace std;

namespace web_ui
{
    GLint renderer::program;
    int renderer::canvas_width;
    int renderer::canvas_height;

    GLuint compile_shader(GLenum type, const char* source)
    {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint info_len = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
            if (info_len > 1)
            {
                char* infoLog = new char[info_len];
                glGetShaderInfoLog(shader, info_len, nullptr, infoLog);
                cerr << "Error compiling shader: " << infoLog << '\n';
                delete[] infoLog;
            }
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }

    GLuint create_program(const char* vertex_source, const char* fragment_source)
    {
        GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_source);
        if (!vertex_shader) return 0;

        GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_source);
        if (!fragment_shader) return 0;

        GLuint program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        GLint linked;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (!linked)
        {
            GLint info_len = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);
            if (info_len > 1)
            {
                char* infoLog = new char[info_len];
                glGetProgramInfoLog(program, info_len, nullptr, infoLog);
                cerr << "Error linking program: " << infoLog << '\n';
                delete[] infoLog;
            }
            glDeleteProgram(program);
            return 0;
        }
        return program;
    }

    void renderer::init()
    {
        const char* vertex_source = R"(
            attribute vec4 position;
            attribute vec4 color;
            varying vec4 vColor;
            void main()
            {
                gl_Position = vec4(position.xy, position.zw);
                vColor = color;
            }
        )";

        const char* fragment_source = R"(
            precision mediump float;
            varying vec4 vColor;
            void main()
            {
                gl_FragColor = vColor;
            }
        )";

        program = create_program(vertex_source, fragment_source);
        if (!program)
        {
            cerr << "Failed to create program\n";
            return;
        }

        glUseProgram(program);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void renderer::draw_line(glm::vec2 p1, glm::vec2 p2, glm::vec3 color)
    {
        float vertices[] = { p1.x, p1.y, p2.x, p2.y };
        float colors[] = { color.r, color.g, color.b, 1.0f, color.r, color.g, color.b, 1.0f };

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, colors);

        glDrawArrays(GL_LINES, 0, 2);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

    void renderer::draw_triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec3 color)
    {
        float vertices[] = { p1.x, p1.y, p2.x, p2.y, p3.x, p3.y };
        float colors[] = { color.r, color.g, color.b, 1.0f, color.r, color.g, color.b, 1.0f, color.r, color.g, color.b, 1.0f };

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, colors);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

    void renderer::draw_rectangle(glm::vec2 p1, glm::vec2 p2, glm::vec3 color)
    {
        float vertices[] = {
            p1.x, p1.y,
            p2.x, p1.y,
            p2.x, p2.y,
            p1.x, p2.y
        };
        float colors[] = {
            color.r, color.g, color.b, 1.0f,
            color.r, color.g, color.b, 1.0f,
            color.r, color.g, color.b, 1.0f,
            color.r, color.g, color.b, 1.0f
        };

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, colors);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

    void renderer::draw_circle(glm::vec2 center, float radius, glm::vec3 color)
    {
        const int num_segments = 100;
        float vertices[2 * (num_segments + 2)];
        float colors[4 * (num_segments + 2)];
        vertices[0] = center.x;
        vertices[1] = center.y;
        colors[0] = color.r;
        colors[1] = color.g;
        colors[2] = color.b;
        colors[3] = 1.0f;

        for (int i = 0; i <= num_segments; ++i)
        {
            float angle = 2.0f * M_PI * float(i) / float(num_segments);
            vertices[2 * (i + 1)] = center.x + radius * cosf(angle);
            vertices[2 * (i + 1) + 1] = center.y + radius * sinf(angle);
            colors[4 * (i + 1)] = color.r;
            colors[4 * (i + 1) + 1] = color.g;
            colors[4 * (i + 1) + 2] = color.b;
            colors[4 * (i + 1) + 3] = 1.0f;
        }

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, colors);

        glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments + 2);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

    void renderer::draw_ellipse(glm::vec2 center, float radius_x, float radius_y, glm::vec3 color)
    {
        const int num_segments = 100;
        float vertices[2 * (num_segments + 2)];
        float colors[4 * (num_segments + 2)];
        vertices[0] = center.x;
        vertices[1] = center.y;
        colors[0] = color.r;
        colors[1] = color.g;
        colors[2] = color.b;
        colors[3] = 1.0f;

        for (int i = 0; i <= num_segments; ++i)
        {
            float angle = 2.0f * M_PI * float(i) / float(num_segments);
            vertices[2 * (i + 1)] = center.x + radius_x * cosf(angle);
            vertices[2 * (i + 1) + 1] = center.y + radius_y * sinf(angle);
            colors[4 * (i + 1)] = color.r;
            colors[4 * (i + 1) + 1] = color.g;
            colors[4 * (i + 1) + 2] = color.b;
            colors[4 * (i + 1) + 3] = 1.0f;
        }

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, colors);

        glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments + 2);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
}
