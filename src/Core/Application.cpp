#include "Core/Application.hpp"
#include "Graphics/GLFW.hpp"

namespace Core {

    std::shared_ptr<Application> Application::instance = nullptr;

    Application::Application(int argc, char* argv[])
    {   
        ConsoleLogger::getInstance()->info("Starting application...");

        std::string new_arg("-f");
        command_line_args.AddArgument(new_arg);
        
        command_line_args.CaptureArgs(argc, argv);
        command_line_args.ProcessArgs();

        //App should start running by default
        running = true;
    }

    void Application::RegisterSignalHandlers() 
    {
        std::signal(SIGINT, signalHandler);
        std::signal(SIGQUIT, signalHandler);

    }

    int Application::Run()
    {   
        
        std::string window_name("Test Window");
        auto glfw_ptr = std::make_shared<Graphics::GLFW>(window_name);   
       
        glfw_ptr->Initialize();
        glfw_ptr->CreateWindow();
        glfwSwapInterval(1);
        

        while(running) {

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(glfw_ptr->window);

            /* Poll for and process events */
            glfwPollEvents();
            
            if(glfwWindowShouldClose(glfw_ptr->window))
            {   
                running = false;
                glfwDestroyWindow(glfw_ptr->window);
            }
        }

       
        glfwTerminate();
        return 0;
    }

}