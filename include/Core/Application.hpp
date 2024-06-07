#pragma once
#ifndef __APPLICATION_HH__
#define __APPLICATION_HH__

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <csignal>
#include <atomic>
#include <type_traits>

#include "Core/Logging.hpp"
#include "Core/CommandLineArgs.hpp"
#include "Core/SignalHandling.hpp"
#include "Core/Layer.hpp"
#include "Core/LayerStack.hpp"

#include "UI/MainWindow.hpp"

namespace Core {

    class Application 
    {
        public:
        
        static std::shared_ptr<Application> GetInstance(int argc = 0, char* argv[] = nullptr)
        {
            if(instance == nullptr)
            {
                instance = std::shared_ptr<Application>(new Application(argc, argv));
            }

            return instance;
        }

        void RegisterSignalHandlers();

        int Run();

        friend int main(int argc, char* argv[]);

        void SetName(std::string& new_name) { name = new_name;}

        std::atomic<bool> running;
        
        private:
        std::string name;

        static std::shared_ptr<Application> instance;

        //Can only call this construct from Application::GetInstance()
        Application(int argc, char* argv[]);
        
        CommandLineArgs command_line_args;

        LayerStack layers;  //Relegate actual logic to layers.  Could this blow up in my face later?  Maybe.  Let's find out!
        
        std::shared_ptr<UI::MainWindow> main_window;
    };

}


#endif