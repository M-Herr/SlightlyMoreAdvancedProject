#include "Core/Layer.hpp"
#include "Core/Logging.hpp"


namespace Core {

    Layer::Layer()
    {
        auto uuid_gen  = Utils::UUIDGenerator::GetInstance(Utils::UUIDVersion::V_ONE, Utils::UUIDVariant::OSF);
        auto start = std::chrono::high_resolution_clock::now();
        uuid = uuid_gen->Generate();
        auto end = std::chrono::high_resolution_clock::now();

        ConsoleLogger::getInstance()->info("UUID generated in: {} ms", std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count());
   
        ConsoleLogger::getInstance()->info("Created layer with UUID: {}", uuid.GetFormatted());
    }   

    void Layer::OnAttach() 
    {

    }

    void Layer::OnDetach()
    {

    }

    void Layer::Update()
    {
    
    }

}