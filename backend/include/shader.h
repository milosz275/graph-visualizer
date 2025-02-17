#ifndef SHADER_H
#define SHADER_H

/**
 * @brief Compiles a given shader source code.
 *
 * @param shader The shader object to compile.
 * @param source The source code of the shader.
 */
void compile_shader(GLuint shader, const char *source);

/**
 * @brief Vertex shader source code.
 */
extern const char *vertex_shader_source;

/**
 * @brief Fragment shader source code.
 */
extern const char *fragment_shader_source;

#endif // SHADER_H
