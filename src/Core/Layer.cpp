#include "Core/Layer.hpp"
#include "Core/Logging.hpp"


namespace Core {

    Layer::Layer()
    {
        auto uuid_gen  = Utils::UUIDGenerator::GetInstance(Utils::UUIDVersion::V_ONE, Utils::UUIDVariant::OSF);
        auto start = std::chrono::high_resolution_clock::now();
        uuid = uuid_gen->Generate();
        auto end = std::chrono::high_resolution_clock::now();
   
        ConsoleLogger::getInstance()->info("Created layer with UUID: {}", uuid.GetFormatted());
    }   

    void Layer::OnAttach() 
    {
        ConsoleLogger::getInstance()->info("OnAttach for layer {} was called.", name);
    }

    void Layer::OnDetach()
    {
        ConsoleLogger::getInstance()->info("OnDetach for layer {} was called.", name);
    }

    void Layer::Update()
    {
        ConsoleLogger::getInstance()->info("Update function in layer {} was called.", name);
    }

}