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
        Buttton();
        ~Button();

        virtual void PreRender() override;
        virtual void Render() override;
        virtual void PostRender() override;


        bool clicked;

    };

}


#endif // __BUTTON_HH__