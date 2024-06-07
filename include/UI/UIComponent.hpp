#pragma once
#ifndef __UI_COMPONENT_HH
#define __UI_COMPONENT_HH

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_stdlib.h"


namespace UI {


    class UIComponent 
    {
        public:

        virtual void PreRender() = 0;
        virtual void Render() = 0;
        virtual void PostRender() = 0;

    };


}
#endif //__UI_COMPONENT_HH