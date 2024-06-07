#pragma once
#ifndef __WINDOW_HH__
#define __WINDOW_HH__

#include "UI/UIComponent.hpp"

namespace UI 
{

class Window : public UIComponent
{
    public:
    Window(std::string& name);

    virtual void Begin() override;
    virtual void End() override;

    std::string name;
};
 
    

}

#endif //__WINDOW_HH__