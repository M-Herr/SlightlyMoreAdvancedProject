#include "Core/Application.hpp"


#include "UI/Window.hpp"


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
        
        UI::WindowProperties properties = 
        {
            .width = 1920,
            .height = 1080,
            .clear_color = {4.0/255.0, 59.0/255.0, 92.0/255.0, 1},
            .name = "Application"
        };

        main_window = std::make_shared<UI::MainWindow>(properties);
        main_window->InitializeGLFW();
        main_window->SetupImgui();
        
        std::string test_name("Test Window");
        UI::Window an_imgui_window(test_name);

        while(running) {    
            main_window->BeginFrame();

            an_imgui_window.Begin();
            
            an_imgui_window.End();

            main_window->EndFrame();
            running = main_window->running;
        }

        main_window->CleanUp();


        return 0;
    }

}