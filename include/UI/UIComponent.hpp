#pragma once
#ifndef __UI_COMPONENT_HH__
#define __UI_COMPONENT_HH__

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_stdlib.h"


namespace UI 
{

    class UIComponent 
    {
        public:

        virtual void Begin() = 0;
        
        virtual void End() = 0;

    };

}

#endif //__UI_COMPONENT_HH