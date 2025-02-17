#ifndef RENDER_H
#define RENDER_H

#include <vector>

using namespace std;

/**
 * @brief Represents the background color mode and RGB values.
 */
struct background
{
    /**
     * @brief Enum for background color modes.
     */
    enum Mode
    {
        LIGHT,
        DARK
    };

    Mode mode;          ///< Current color mode.
    float light_rgb[3]; ///< RGB values for light mode.
    float dark_rgb[3];  ///< RGB values for dark mode.

    /**
     * @brief Constructs a background object with default color mode set to dark.
     */
    background();

    /**
     * @brief Sets the background color mode.
     * @param new_mode The new color mode to set.
     */
    void set_mode(Mode new_mode);

    /**
     * @brief Gets the current RGB values based on the color mode.
     * @return Pointer to the current RGB values.
     */
    const float *get_current_rgb() const;
};

/**
 * @brief Represents a circle with position, size, and color.
 */
class circle
{
public:
    float x, y;    ///< Position of the circle in the -1.0f - 1.0f domain.
    float size;    ///< Size of the circle.
    float r, g, b; ///< Color of the circle.
};

/**
 * @brief Represents an edge with start and end positions and color.
 */
class edge
{
public:
    float start_x, start_y; ///< Start position of the edge.
    float end_x, end_y;     ///< End position of the edge.
    float r, g, b;          ///< Color of the edge.
    float weight;           ///< Weight of the edge.
};

/**
 * @brief Initializes an example graph with predefined nodes and edges.
 */
void init_example_graph();

/**
 * @brief Generates render data for circles representing graph nodes.
 * @return A vector of floats containing the render data.
 */
vector<float> generate_circle_render_data();

/**
 * @brief Generates render data for edges representing graph connections.
 * @return A vector of floats containing the render data.
 */
vector<float> generate_edge_render_data();

/**
 * @brief Initializes OpenGL settings and shaders.
 */
void init_gl();

/**
 * @brief Updates the graph data for rendering.
 */
void update_graph();

/**
 * @brief Renders the graph on the canvas.
 */
void render();

#endif // RENDER_H
