#pragma once
#ifndef __COMMAND_LINE_ARGS_HH__
#define __COMMAND_LINE_ARGS_HH__

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include "Core/Logging.hpp"

namespace Core {

    
    class CommandLineArgs {
        public:

        using ArgPair = std::pair<std::string, std::string>; //Arguments will be a flag(-f, -v, etc) and a value

        void CaptureArgs(int argc, char* argv[]);
        void ProcessArgs();
        void AddArgument(std::string& flag);



        private:
        std::vector<ArgPair> arguments;
        std::vector<std::string> passed_arguments;
        std::vector<std::string> flags;
    };
}


#endif // __COMMAND_LINE_ARGS_HH__ 