#pragma once

namespace web_ui
{
    class background
    {
    private:
        static int darkmode;

    public:
        /**
         * Toggles and returns new darkmode state, can be either true or false.
         */
        static bool toggle_darkmode();

        /**
         * Returns new darkmode state, can be either true or false.
         */
        static bool get_darkmode();

        /**
         * Draw static background, gray on default
         */
        static void draw_background();
    };
}
