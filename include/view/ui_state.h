#pragma once

#include <string>
#include <memory>
#include <vector>

#include "ui_element.h"
#include "graph.h"
#include "graph_algorithm.h"

using namespace std;

namespace mvc
{
    class ui_state
    {
    public:
        virtual ~ui_state() = default;
        
        /**
         * Renders menu and the graph
         */
        virtual void render() = 0;
        
        virtual void handle_click(float mouse_x, float mouse_y, bool down) = 0;
    };

    class menu_state : public ui_state
    {
    private:
        vector<unique_ptr<mvc::ui_element>> elements;
    public:
        menu_state();
        ~menu_state() override;
        void render() override;
        void handle_click(float mouse_x, float mouse_y, bool down) override;
    };
    
    // graph screen (renders graph after generation)
    class graph_state : public ui_state
    {
    private:
        unique_ptr<mvc::graph> graph;
        vector<unique_ptr<mvc::ui_element>> elements;
    public:
        graph_state(unique_ptr<mvc::graph> graph);
        ~graph_state() override;
        void render() override;
        void handle_click(float mouse_x, float mouse_y, bool down) override;
    };
    
    // algorithm execution state
    class algorithm_state : public ui_state
    {
    private:
        unique_ptr<mvc::graph> graph;
        unique_ptr<mvc::graph_algorithm> algorithm;
    public:
        algorithm_state(unique_ptr<mvc::graph_algorithm> algorithm, unique_ptr<mvc::graph> graph);
        ~algorithm_state() override;
        void render() override;
        void handle_click(float mouse_x, float mouse_y, bool down) override;
    };
}
