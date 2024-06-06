#include "Graphics/GLFW.hpp"
#include <GLFW/glfw3.h>
#include "hello_imgui/hello_imgui.h"


namespace Graphics {

    void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }


    GLFW::GLFW(std::string& in_window_name)
    : window_name(in_window_name)
    {

    }

    GLFW::~GLFW()
    {
        if(window)
        {
            glfwDestroyWindow(window);
        }
    }

    int GLFW::Initialize()
    {   
        
        if(!glfwInit())
        {
             ConsoleLogger::getInstance()->error("GLFW failed to Init.");
             return -1;
        }

        glfwSetErrorCallback(error_callback);
      

        return 0;
    }
    
    int GLFW::CreateWindow()
    {
        window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);

        if(window == nullptr)
        {
            ConsoleLogger::getInstance()->error("Failed to create a window.");
            glfwTerminate();
            return -1;
        }

        glfwSetKeyCallback(window, key_callback);

        glfwMakeContextCurrent(window);
        gladLoadGL();
        
        return 0;
    }




}