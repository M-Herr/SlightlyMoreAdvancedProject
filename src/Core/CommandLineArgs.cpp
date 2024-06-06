#include "Core/CommandLineArgs.hpp"




namespace Core 
{
    void CommandLineArgs::CaptureArgs(int argc, char* argv[])
    {
        //argc is number of arguments
        passed_arguments.reserve(argc);

        for(size_t i = 0; i < argc; i++)
        {
            passed_arguments.emplace_back(argv[i]);
        }
    }

    void CommandLineArgs::ProcessArgs()
    {
        bool found_args = false;
        for(auto& arg : passed_arguments)
        {
            if(std::find(std::begin(flags), std::end(flags), arg) != std::end(flags))
            {
                ConsoleLogger::getInstance()->info("An input flag {} matches our pre-defined flags.", arg);
            }
        }

        if(!found_args)
        {
            ConsoleLogger::getInstance()->info("No input arguments received.");
        }
    }

    void CommandLineArgs::AddArgument(std::string& flag) 
    {

        auto it = std::find(std::begin(flags), std::end(flags), flag);
        if(it != std::end(flags))
        {
            flags.emplace_back(flag);
        }

    }

}