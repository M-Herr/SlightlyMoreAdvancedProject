#include "Core/SignalHandling.hpp"
#include "Core/Application.hpp"


namespace Core 
{
    void signalHandler(int signum) {
        //Get handle to Application in case we need to kill it
        auto app = Application::GetInstance();
        auto console_logger = ConsoleLogger::getInstance();

        switch(signum)
        {
            case SIGINT:
            {
                console_logger->warn("Got a SIGINT, shutting down the application.");
                if(app->running)
                {
                    app->running = false;
                }
                break;
            }
            case SIGQUIT:
            {
                console_logger->warn("Got a SIGQUIT, shutting down the application.");
                if(app->running)
                {
                    app->running = false;
                }
                break;
            }
            default:
            {
                console_logger->warn("Got some unkown signal, that's deeply conerning!");
                break;
            }
           
        }

    }
}