#pragma once
#ifndef __LAYER_STACK_HH
#define __LAYER_STACK_HH

#include <vector>


namespace Core {
class Layer;

    class LayerStack 
    {
        public:

        LayerStack() = default;
        ~LayerStack() = default;

        void AddLayer(Layer& layer);

        LayerStack(LayerStack&& other) noexcept
        {
            std::swap(layers, other.layers);
        }

        LayerStack& operator=(LayerStack&& other) noexcept
        {
            std::swap(layers, other.layers);
            return *this;
        }


        LayerStack(const LayerStack& other) = delete; //Delete copy 
        LayerStack& operator=(const LayerStack& other) = delete; //Delete copy assignment

        std::vector<Layer> layers;

    };

}
#endif // __LAYER_STACK_HH