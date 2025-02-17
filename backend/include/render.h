#ifndef RENDER_H
#define RENDER_H

#include <vector>

using namespace std;

/**
 * @brief Represents the color scheme light and dark mode with corresponding RGB values.
 */
struct color_scheme
{
    /**
     * @brief Enum for available color modes.
     */
    enum Mode
    {
        LIGHT,
        DARK
    };

    Mode mode;                     ///< Current color mode.
    
    float light_rgb_background[3];      ///< background RGB values for light mode.
    float light_rgb_selected_circle[3]; ///< selected circle RGB values for light mode.
    float light_rgb_circle[3];          ///< circle RGB values for light mode.
    float light_rgb_line[3];            ///< line RGB values for light mode.

    float dark_rgb_background[3];      ///< background RGB values for dark mode.
    float dark_rgb_selected_circle[3]; ///< selected circle RGB values for dark mode.
    float light_rgb_circle[3];         ///< circle RGB values for light mode.
    float dark_rgb_circle[3];          ///< circle RGB values for dark mode.
    float dark_rgb_line[3];            ///< line RGB values for dark mode.

    /**
     * @brief Constructs a color scheme object with default color mode set to dark.
     */
    color_scheme();

    /**
     * @brief Sets the background color mode.
     * @param new_mode The new color mode to set.
     */
    void set_mode(Mode new_mode);

    /**
     * @brief Gets the current RGB values for the background based on the color mode.
     * @return Pointer to the current RGB values.
     */
    const float *get_background_rgb() const;

    /**
     * @brief Gets the current RGB values for the selected circle based on the color mode.
     * @return Pointer to the current RGB values.
     */
    const float *get_selected_circle_rgb() const;

    /**
     * @brief Gets the current RGB values for the circle based on the color mode.
     * @return Pointer to the current RGB values.
     */
    const float *get_circle_rgb() const;

    /**
     * @brief Gets the current RGB values for the line based on the color mode.
     * @return Pointer to the current RGB values.
     */
    const float *get_line_rgb() const;
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
 * @brief Represents an line with start and end positions and color.
 */
class line
{
public:
    float start_x, start_y; ///< Start position of the line.
    float end_x, end_y;     ///< End position of the line.
    float r, g, b;          ///< Color of the line.
    float weight;           ///< Weight of the line.
};

/**
 * @brief Initializes an example graph with predefined nodes and lines.
 */
void init_example_graph();

/**
 * @brief Generates render data for circles representing graph nodes.
 * @return A vector of floats containing the render data.
 */
vector<float> generate_circle_render_data();

/**
 * @brief Generates render data for lines representing graph connections.
 * @return A vector of floats containing the render data.
 */
vector<float> generate_line_render_data();

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
