
#include "Core/Application.hpp"



int main(int argv, char* argc[]) 
{

    std::shared_ptr<Core::Application> App = Core::Application::GetInstance(argv, argc);
    App->RegisterSignalHandlers();
    App->Run();
    
    return EXIT_SUCCESS;
};