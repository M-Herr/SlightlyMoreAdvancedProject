#include "Core/LayerStack.hpp"
#include "Core/Layer.hpp"

namespace Core {

    void LayerStack::AddLayer(std::shared_ptr<Layer> layer)
    {
        layers.emplace_back(layer);
    }

}