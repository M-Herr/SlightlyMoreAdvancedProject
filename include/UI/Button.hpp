#pragma once
#ifndef __BUTTON_HH__
#define __BUTTON_HH__
#include <string>

#include "UI/UIComponent.hpp"

namespace UI 
{
    class Button : public UIComponent
    {
        public:
        Button(std::string& name);
        ~Button();

        virtual void Begin() override;
        virtual void End() override;

        bool clicked;
        std::string button_text;
    };

}


#endif // __BUTTON_HH__