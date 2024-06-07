#pragma once
#ifndef __MAIN_WINDOW_HH__
#define __MAIN_WINDOW_HH__

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

namespace UI {

    typedef struct
    {
        size_t width;
        size_t height;
        ImVec4 clear_color;
        std::string name;
    } WindowProperties;

    class MainWindow
    {
        public:
        MainWindow(WindowProperties in_properties);
        ~MainWindow();

        void InitializeGLFW();

        void SetupImgui();

        void BeginFrame();

        void EndFrame();

        void CleanUp();
        

        bool running;
        private:

        GLFWwindow* window;
        WindowProperties properties;
        
    };

}
#endif