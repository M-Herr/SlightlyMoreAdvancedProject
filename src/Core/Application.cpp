#include "Core/Application.hpp"

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

        Layer test_layer;

        layers.AddLayer(test_layer);

        
        while(running) {

            for(auto& layer : layers.layers)
            {
                layer.Update();
            }

        }

        return 0;
    }

}