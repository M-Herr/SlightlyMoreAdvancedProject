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

        Layer(const Layer& other) {
            this->name = other.name;
            this->uuid = other.uuid;
        }

        Layer(Layer&& other) noexcept
        {
            std::swap(name, other.name);
            std::swap(uuid, other.uuid);
        }

        Layer& operator=(Layer&& other) noexcept
        {
            std::swap(name, other.name);
            std::swap(uuid, other.uuid);
            return *this;
        }

        Layer& operator=(const Layer& other)
        {
            this->name = other.name;
            this->uuid = other.uuid;

            return *this;
        }

        virtual void OnAttach();
        virtual void Update();
        virtual void OnDetach();

        std::string name;
        Utils::uuid uuid;
    };
}

#endif //__LAYER_HH__