#pragma once
#ifndef __GLFW_LOOP_HH__
#define __GLFW_LOOP_HH__

#include <memory>
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Core/Logging.hpp"


namespace Graphics {

    class GLFW
    {
        public:
        GLFW(std::string& in_window_name);
        ~GLFW();

        int Initialize();
        
        int CreateWindow();

        GLFWwindow* window;
        std::string window_name;

        std::atomic<bool> running;
    };

}

#endif //__GLFW_LOOP_HH__