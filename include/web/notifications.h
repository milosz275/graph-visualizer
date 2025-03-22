#pragma once

#include <string>
#include <list>
#include <chrono>

#include <glm/vec2.hpp>

namespace web_ui
{
    class notifications
    {
    private:
        static int target_size;
        static std::list<std::pair<std::string, std::chrono::steady_clock::time_point>> texts; // (text, start timestamp)
        static glm::vec2 upper_left_corner;

        /**
         * @brief Removes timed out notifications from the list.
         */
        static void update();
        
    public:
        /**
         * @brief Draws first n notifications from the list.
         * @note n is target_size, static set in "notifications.cpp"
         */
        static void draw();

        /**
         * @brief Adds new notification.
         * @param text Text label of the notification.
         * @param duration Time duration to show the notification on screen.
         */
        static void add(std::string text, int duration);
    };
}
