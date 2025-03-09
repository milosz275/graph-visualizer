#pragma once

#include <string>
#include <functional>

using namespace std;

namespace mvc
{
    class ui_element
    {
    protected:
        float x, y;
        float width, height;

    public:
        virtual ~ui_element() = default;

        virtual void render() = 0;
        virtual bool is_clicked(float mouse_x, float mouse_y);
        virtual void on_click() = 0;
    };

    class ui_button : public ui_element
    {
    private:
        string label;
        function<void()> callback;

    public:
        ui_button(float x, float y, float width, float height, string label, function<void()> callback);
        void render() override;
        void on_click() override;
    };

    class ui_label : public ui_element
    {
    private:
        string text;

    public:
        ui_label(float x, float y, string text);
        void render() override;
        bool is_clicked(float, float) override;
        void on_click() override;
    };
}
