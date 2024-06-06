#pragma once
#ifndef __LAYER_HH__
#define __LAYER_HH__

#include <string>

#include "Util/UUID.hpp"

namespace Core {
    class Layer 
    {
        public:
        Layer();
        ~Layer() = default;

        void OnAttach();
        void Update();
        void OnDetach();

        std::string name;
        Utils::uuid uuid;
    };
}

#endif //__LAYER_HH__